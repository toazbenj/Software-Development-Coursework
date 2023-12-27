/**
 * @file EatVisitor.cpp
 * @author Ben Toaz
 *
 * Handles all eating functionality for sparty outside of animations.
 * Is actually visiting all items in sudoku to get needed info and manipulate
 * the vector of items. Will need to pass pointer to sudoku into mouth moving function
 * for sparty.
 */

#include "pch.h"
#include "XRayVisitor.h"
#include "EatVisitor.h"
#include "Sudoku.h"
#include "ItemXRay.h"

using namespace std;

/**
 * Constructor
 * @param x Sparty move coord x
 * @param y Sparty move coord y
 */
EatVisitor::EatVisitor(double x, double y)
{
    mTargetX = x;
    mTargetY = y;
}

/**
 * See if digit is within range of sparty.
 * If so, save the item and get rid of it in the vector
 * @param digit eaten digit
 */
void EatVisitor::VisitDigitMovable(ItemDigitMovable *digit)
{
    auto minX = digit->GetCol() * digit->GetWidth();
    auto maxX = digit->GetCol() * digit->GetWidth() + digit->GetWidth();
    auto minY = digit->GetRow() * digit->GetHeight();
    auto maxY = digit->GetRow() * digit->GetHeight() + digit->GetHeight();

    if(mTargetX >= minX && mTargetX <= maxX && mTargetY >= minY && mTargetY <= maxY)
    {
        mEatenDigit = digit;
    }
}

/**
 * Find the xray item, deposit the saved digit inside
 * @param xray
 */
void EatVisitor::VisitXRay(ItemXRay *xray)
{
}

/**
 * Put digit into xray
 */
void EatVisitor::SendToXRay()
{
    if(mEatenDigit == nullptr)
    {
        return;
    }
    XRayVisitor visitor;
    auto sudoku = mEatenDigit->GetSudoku();
    sudoku->Accept(&visitor);

    auto xRay = visitor.GetXRay();
    if(xRay->GetNumDigits() >= 7)
    {
        sudoku->GetPopupManager()->AddFull();
        return;
    }

    auto sharedDigit = sudoku->PopDigit(mEatenDigit);
    xRay->AddDigit(sharedDigit);
}

