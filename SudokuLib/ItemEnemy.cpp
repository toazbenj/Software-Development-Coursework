/**
 * @file ItemEnemy.cpp
 * @author Abhi Rao
 *
 * Pursuer for Sparty
 */

#include "pch.h"
#include "ItemEnemy.h"
#include "DeclarationSparty.h"
#include "DeclarationEnemy.h"
#include "XRayVisitor.h"
#include "ContainerVisitor.h"
#include "Sudoku.h"
#include "ItemXRay.h"
#include "XRayVisitor.h"
#include <wx/graphics.h>

using namespace std;

/// Character speed in pixels per second
const double MaxSpeed = 100.00;

/**
 * Constructor
 * @param declaration image information for enemy
 * @param sudoku Sudoku object to which enemy belongs
 */
ItemEnemy::ItemEnemy(Sudoku *sudoku, DeclarationEnemy *declaration) : Item(sudoku)
{
    mDeclaration = declaration;
}

/**
 * Load enemy from XML
 *
 * @param node the tag containing enemy item info
 */
void ItemEnemy::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
    mTarget = make_unique<wxRealPoint>(GetCol() * GetLevelTileWidth(), GetRow() * GetLevelTileHeight());
}

/**
 * Draws Enemy
 *
 * @param graphics Graphics context to draw on
 */
void ItemEnemy::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double x = GetCol() * (mDeclaration->GetWidth() / 2.0);
    double y = GetRow() * (mDeclaration->GetHeight() / 2.0);

    graphics->PushState();
    graphics->Translate(x, y);
    mDeclaration->Draw(graphics, 0, 0);

    graphics->PopState();
}

/**
 * @return width of the declaration object
 */
double ItemEnemy::GetWidth() const
{
    return mDeclaration->GetWidth();
}

/**
 * @return height of the declaration object
 */
double ItemEnemy::GetHeight() const
{
    return mDeclaration->GetHeight();
}

/**
 *  * Set the point to which enemy will move
 * @param x coord
 * @param y coord
 * @param moving flag
 * @param pixelWidth playing area size
 * @param pixelHeight playing area size
 */
void ItemEnemy::SetTarget(double x, double y, bool moving, double pixelWidth, double pixelHeight)
{
    if ((x < pixelWidth) && (x > 0) && (0 < y) && (y < pixelHeight))
    {
        mTarget->x = x - mDeclaration->GetTargetX();
        mTarget->y = y + mDeclaration->GetTargetY();
        mIsMoving = moving;
    }
}

/**
 * Updates position and speed of Enemy
 *
 * @param elapsed time since last update
 */
void ItemEnemy::Update(double elapsed)
{
    double row = GetRow();
    double col = GetCol();

    double distance = sqrt(pow(mTarget->x - col * GetLevelTileWidth(), 2) + pow(mTarget->y - row * GetLevelTileHeight(), 2));

    if (distance > 10)
    {
        double newRow = row + MaxSpeed * elapsed * (mTarget->y / GetLevelTileHeight() - row) / distance;
        double newCol = col + MaxSpeed * elapsed * (mTarget->x / GetLevelTileWidth() - col) / distance;
        SetLocation(newCol, newRow);
        mIsMoving = true;
    }
    else
    {
        mIsMoving = false;
    }

    double maxRow = GetSudoku()->GetLevel()->GetHeight();
    double maxCol = GetSudoku()->GetLevel()->GetWidth();

    if (GetRow() > maxRow)
    {
        mIsMoving = false;
        SetRow(maxRow);
        mTarget->x = GetCol() * GetLevelTileWidth();
        mTarget->y = GetRow() * GetLevelTileHeight();
    }
    else if (GetCol() > maxCol - 2)
    {
        mIsMoving = false;
        SetCol(maxCol-2);
        mTarget->x = GetCol() * GetLevelTileWidth();
        mTarget->y = GetRow() * GetLevelTileHeight();
    }
    else if (GetCol() < 0)
    {
        mIsMoving = false;
        SetCol(0);
        mTarget->x = GetCol() * GetLevelTileWidth();
        mTarget->y = GetRow() * GetLevelTileHeight();
    }
    else if (GetRow() < 1)
    {
        mIsMoving = false;
        SetRow(1);
        mTarget->x = GetCol() * GetLevelTileWidth();
        mTarget->y = GetRow() * GetLevelTileHeight();
    }
    /*double spartyX = mSpartyDeclaration->GetCol() * GetLevelTileWidth();
    double spartyY = mSpartyDeclaration->GetRow() * GetLevelTileHeight();
    if (mSpartyDeclaration->HitTest(GetCol() * GetLevelTileWidth(), GetRow() * GetLevelTileHeight())
    {
        mXrayDeclaration->RelseaseDigits();
    }*/
    auto sparty = GetSudoku()->GetSparty();
    double spartyX = sparty->GetCol() * GetLevelTileWidth();
    double spartyY = sparty->GetRow() * GetLevelTileHeight() - sparty->GetDeclaration()->GetWidth();
    double spartyW = sparty->GetDeclaration()->GetWidth();
    double spartyH = sparty->GetDeclaration()->GetHeight();

    double x = GetCol() * GetLevelTileWidth();
    double y = GetRow() * GetLevelTileHeight();
    double w = GetDeclaration()->GetWidth();
    double h = GetDeclaration()->GetHeight();

    if((x < spartyX + 0.5 * spartyW) && (x + 0.5 * w > spartyX) && (y - 0.5 * h < spartyY + spartyH) && (y - 0.5 * h > spartyY))
    {
        SetLocation(0, 0);
        mTarget->x = 0;
        mTarget->y = 0;

        XRayVisitor visitor;
        GetSudoku()->Accept(&visitor);

        //GetSudoku()->GetPopupManager()->GetCaught()->SetTimeCaught(elapsed);
        GetSudoku()->GetPopupManager()->GetCaught()->Initialize(GetSudoku()->GetPopupManager()->GetCaught()->GetElapsed());
        mSound->Play(L"Audio/Owen.wav");
        auto xRay = visitor.GetXRay();
        xRay->ReleaseDigits();
    }

    this->GetSudoku()->MoveEnemyFront();
}

