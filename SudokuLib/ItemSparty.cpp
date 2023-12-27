/**
 * @file ItemSparty.cpp
 * @author Peyton Nagher, Stefan Lemke
 */

#include "pch.h"
#include "ItemSparty.h"
#include "DeclarationSparty.h"
#include "SpartyVisitor.h"
#include "XRayVisitor.h"
#include "ContainerVisitor.h"
#include "ItemDigitVisitor.h"
#include "EatVisitor.h"
#include "RegurgitateVisitor.h"
#include "Sudoku.h"
#include "ItemXRay.h"
#include <wx/graphics.h>

using namespace std;

/// Character speed in pixels per second
const double MaxSpeed = 400.00;

/// The time for an eating cycles in seconds
const double EatingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

/**
 * Constructor
 * @param declaration image information for sparty
 * @param sudoku Sudoku object to which Sparty belongs
 */
ItemSparty::ItemSparty(Sudoku *sudoku, DeclarationSparty *declaration) : Item(sudoku)
{
    mDeclaration = declaration;
    mIsEating = false;
    mIsRegurgitating = false;
    mIsHeadbutting = false;
}

/**
 * Function to load an ItemSparty object into the game from XML
 *
 * @param node represents an XML node for ItemSparty
 */
void ItemSparty::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
    mTarget = make_unique<wxRealPoint>(GetCol() * GetLevelTileWidth(), GetRow() * GetLevelTileHeight());
}

/**
 * Draws Sparty
 *
 * @param graphics Graphics context to draw on
 */
void ItemSparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double headCurrentAngle;
    double headPivotAngle = mDeclaration->GetHeadPivotAngle();
    double x = GetCol() * (mDeclaration->GetWidth() / 2.0);
    double y = GetRow() * (mDeclaration->GetHeight() / 2.0);

    if (mHeadbuttTime < HeadbuttTime / 2.0)
    {
        headCurrentAngle = (mHeadbuttTime / (HeadbuttTime / 2.0)) * headPivotAngle;
    }
    else
    {
        headCurrentAngle = headPivotAngle - ((mHeadbuttTime - (HeadbuttTime / 2.0)) / (HeadbuttTime / 2.0)) * headPivotAngle;
    }

    graphics->PushState();
    graphics->Translate(x, y);
    graphics->Rotate(headCurrentAngle);

    double mouthCurrentAngle;
    double mouthPivotAngle = mDeclaration->GetMouthPivotAngle();
    double mouthPivotX = mDeclaration->GetMouthPivotX();
    double mouthPivotY = mDeclaration->GetMouthPivotY() - mDeclaration->GetHeight();

    if (mMoveMouthTime < EatingTime / 2.0)
    {
        mouthCurrentAngle = (mMoveMouthTime / (EatingTime / 2.0)) * mouthPivotAngle;
    }
    else
    {
        mouthCurrentAngle = mouthPivotAngle - ((mMoveMouthTime - (EatingTime / 2.0)) / (EatingTime / 2.0)) * mouthPivotAngle;
    }

    if(mDeclaration->GetFront() == 1)
    {
        graphics->PushState();
        graphics->Translate(mouthPivotX, mouthPivotY);
        graphics->Rotate(mouthCurrentAngle);
        graphics->Translate(-mouthPivotX, -mouthPivotY);
        mDeclaration->DrawMouth(graphics, 0, 0);
        graphics->PopState();
        mDeclaration->DrawHead(graphics, 0, 0);
    }
    else
    {
        mDeclaration->DrawHead(graphics, 0, 0);
        graphics->PushState();
        graphics->Translate(mouthPivotX, mouthPivotY);
        graphics->Rotate(mouthCurrentAngle);
        graphics->Translate(-mouthPivotX, -mouthPivotY);
        mDeclaration->DrawMouth(graphics, 0, 0);
        graphics->PopState();
    }

    graphics->PopState();
}

/**
 * Function to move Sparty's mouth based on if he is eating or regurgitating
 *
 * @param option eating or regurgitating
 * @param targetNum number that will be eaten or regurgitated
 */
void ItemSparty::MoveMouth(const string& option, const int& targetNum)
{
    if(mIsHeadbutting)
    {
        return;
    }

    mMouthOpen = false;
    if (option == "eat")
    {
        if (!mIsMoving)
        {
            mIsEating = true;
        }
    }
    if (option == "regurgitate")
    {
        if (!mIsMoving)
        {
            mIsRegurgitating = true;
            mTargetNum = targetNum;
        }
    }
}

/**
 * Sets headbutting flag to allow Sparty to headbutt
 */
void ItemSparty::Headbutt()
{
    if (!mIsMoving && !mIsEating && !mIsRegurgitating)
    {
        mIsHeadbutting = true;
        mHasHeadbutt = false;
    }
    else
    {
        mIsHeadbutting = false;
    }
}

/**
 * Updates position and speed of Sparty
 *
 * @param elapsed time since last update
 */
void ItemSparty::Update(double elapsed)
{
    double row = GetRow();
    double col = GetCol();
    double distance = sqrt(pow(mTarget->x - col * GetLevelTileWidth(), 2) + pow(mTarget->y - row * GetLevelTileHeight(), 2));

    if (distance > 15)
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

    if (mIsEating && !mIsHeadbutting)
    {
        mMoveMouthTime += elapsed;

        if (!mMouthOpen && mMoveMouthTime >= EatingTime / 2)
        {
            auto x = mTarget->x + mDeclaration->GetTargetX();
            auto y = mTarget->y - mDeclaration->GetTargetY();

            EatVisitor visitor(x, y);
            GetSudoku()->Accept(&visitor);
            visitor.SendToXRay();

            mMouthOpen = true;
        }
        if (mMoveMouthTime >= EatingTime)
        {
            mIsEating = false;
            mMoveMouthTime = 0;
        }
    }

    if (mIsRegurgitating && !mIsHeadbutting)
    {
        mMoveMouthTime += elapsed;

        if (!mMouthOpen && mMoveMouthTime >= EatingTime / 2)
        {
            auto x = mTarget->x + mDeclaration->GetTargetX();
            auto y = mTarget->y - mDeclaration->GetTargetY();

            XRayVisitor xVisitor;
            GetSudoku()->Accept(&xVisitor);
            auto xRay = xVisitor.GetXRay();

            auto level = GetSudoku()->GetLevel();
            RegurgitateVisitor visitor(mTargetNum, level->GetTileWidth(), level->GetBoardBounds());
            xRay->ContentsAccept(&visitor);
            visitor.SendToGameBoard(x, y);
            GetSudoku()->MoveSpartyFront();

            if(!visitor.GetCanPlaceHere())
            {
                this->GetSudoku()->GetPopupManager()->AddCollision();
            }

            mMouthOpen = true;
        }
        if (mMoveMouthTime >= EatingTime)
        {
            mIsRegurgitating = false;
            mMoveMouthTime = 0;
        }
    }

    if (mIsHeadbutting && !mIsEating && !mIsRegurgitating)
    {
        mHeadbuttTime += elapsed;

        if (!mHasHeadbutt && mHeadbuttTime >= HeadbuttTime / 2)
        {
            auto x = mTarget->x + mDeclaration->GetTargetX();
            auto y = mTarget->y - mDeclaration->GetTargetY();

            ContainerVisitor visitor(x, y);
            GetSudoku()->Accept(&visitor);
            GetSudoku()->MoveSpartyFront();

            mHasHeadbutt = true;
        }

        if (mHeadbuttTime >= HeadbuttTime)
        {
            mIsHeadbutting = false;
            mHeadbuttTime = 0;
        }
    }
}


/**
 * Set the point to which it will move
 * @param x coord
 * @param y coord
 * @param moving flag
 * @param pixelWidth playing area size
 * @param pixelHeight playing area size
 */
void ItemSparty::SetTarget(double x, double y, bool moving, double pixelWidth, double pixelHeight)
{
    if ((x < pixelWidth) && (x > 0) && (0 < y) && (y < pixelHeight))
    {
        mTarget->x = x - mDeclaration->GetTargetX();
        mTarget->y = y + mDeclaration->GetTargetY();
        mIsMoving = moving;
    }
}
