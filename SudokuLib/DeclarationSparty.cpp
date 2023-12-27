/**
 * @file DeclarationSparty.cpp
 *
 * @author Peyton Nagher, Ethan Egger
 *
 */

#include "pch.h"
#include "DeclarationSparty.h"
#include "Sudoku.h"
#include <wx/graphics.h>
#include <sstream>

using namespace std;

/**
 * Constructor
 * @param node declaration node in XML file
 */
DeclarationSparty::DeclarationSparty(wxXmlNode *node) : Declaration(node)
{
    node->GetAttribute(L"width").ToInt(&mWidth);
    node->GetAttribute(L"height").ToInt(&mHeight);
    node->GetAttribute(L"front").ToInt(&mFront);
    node->GetAttribute(L"head-pivot-angle").ToDouble(&mHeadPivotAngle);
    node->GetAttribute(L"head-pivot-x").ToDouble(&mHeadPivotX);
    node->GetAttribute(L"head-pivot-y").ToDouble(&mHeadPivotY);
    node->GetAttribute(L"mouth-pivot-angle").ToDouble(&mMouthPivotAngle);
    node->GetAttribute(L"mouth-pivot-x").ToDouble(&mMouthPivotX);
    node->GetAttribute(L"mouth-pivot-y").ToDouble(&mMouthPivotY);
    node->GetAttribute(L"target-x").ToDouble(&mTargetX);
    node->GetAttribute(L"target-y").ToDouble(&mTargetY);

    wstringstream filename1;
    filename1 << L"Images/" << node->GetAttribute(L"image1");
    wstringstream filename2;
    filename2 << L"Images/" << node->GetAttribute(L"image2");

    mImage1 = make_shared<wxImage>(filename1.str(), wxBITMAP_TYPE_ANY);
    mImage2 = make_shared<wxImage>(filename2.str(), wxBITMAP_TYPE_ANY);
    mBitmap1 = make_shared<wxBitmap>(*mImage1);
    mBitmap2 = make_shared<wxBitmap>(*mImage2);

}

/**
 * Links ItemSparty with its declaration
 *
 * @param sudoku object representing an instance of the Sudoku board
 * @param node node to assign to the sparty item object
 * @return
 */
shared_ptr<Item> DeclarationSparty::Create(Sudoku *sudoku, wxXmlNode *node)
{
    auto item = std::make_shared<ItemSparty>(sudoku, this);
    sudoku->SetSparty(item);
    return item;
}

/**
 * Draw the bitmap objects associated with sparty
 *
 * @param graphics Graphics context to draw with
 * @param row Sparty's row on the screen
 * @param col Sparty's column on the screen
 * @param mouthOpen bool flag
 * @param moveTime time during movement
 * @param eatTime time offset for eating
 */
void DeclarationSparty::Draw(shared_ptr<wxGraphicsContext> graphics, double row, double col, bool mouthOpen, double moveTime, double eatTime)
{
    double width = GetWidth();
    double height = GetHeight();

    double x = col * GetWidth();
    double y = GetHeight() * (row - 1);

    if(mFront == 1)
    {
        graphics->DrawBitmap(*mBitmap2, x, y, width, height);
        graphics->DrawBitmap(*mBitmap1, x, y, width, height);
    }
    else
    {
        graphics->DrawBitmap(*mBitmap1, x, y, width, height);
        graphics->DrawBitmap(*mBitmap2, x, y, width, height);
    }
}

/**
 * Draw the mouth bitmaps for Sparty
 *
 * @param graphics Graphics context to draw with
 * @param row Sparty's row on the screen
 * @param col Sparty's column on the screen
 */
void DeclarationSparty::DrawMouth(shared_ptr<wxGraphicsContext> graphics, double row, double col)
{

    double x = col * GetWidth();
    double y = GetHeight() * (row - 1);

    graphics->DrawBitmap(*mBitmap2, x, y, GetWidth(), GetHeight());
}

/**
 * Draw the head bitmaps for Sparty
 *
 * @param graphics Graphics context to draw with
 * @param row Sparty's row on the screen
 * @param col Sparty's column on the screen
 */
void DeclarationSparty::DrawHead(shared_ptr<wxGraphicsContext> graphics, double row, double col)
{
    double width = GetWidth();
    double height = GetHeight();

    double x = col * GetWidth();
    double y = GetHeight() * (row - 1);

    graphics->DrawBitmap(*mBitmap1, x, y, width, height);
}