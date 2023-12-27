/**
 * @file RegurgitateVisitor.cpp
 *
 * @author Ben Toaz, Peyton Nagher
 *
 * Functionality for moving digit from xray to play area
 */

#include "pch.h"
#include "RegurgitateVisitor.h"
#include "XRayVisitor.h"
#include "DeclarationDigit.h"
#include "Sudoku.h"

using namespace std;

/**
 * Constructor for visitor
 * @param val digit value
 * @param size virtual pixel size
 * @param boardBounds vector of ints
 */
RegurgitateVisitor::RegurgitateVisitor(int val, int size, std::vector<int> boardBounds)
{
    mTargetVal = val;
    mTileSize = size;
    mRowLowerBound = boardBounds[0];
    mColLowerBound = boardBounds[1];
}

/**
 * See if digit is within range of sparty.
 * If so, save the item and get rid of it in the vector
 * Gets digit value from xray
 *
 * @param digit
 */
void RegurgitateVisitor::VisitDigitMovable(ItemDigitMovable *digit)
{
    if (mRegurgitatedDigit == nullptr && digit->GetDeclaration()->GetValue() == mTargetVal)
    {
        mRegurgitatedDigit = digit;
    }
}

/**
 * Facilitates regurgitating a digit back onto
 * the Sudoku game board
 *
 * @param x
 * @param y
 */
void RegurgitateVisitor::SendToGameBoard(double x, double y)
{
    mCanPlaceHere = true;

    if (mRegurgitatedDigit == nullptr)
    {
        return;
    }

    XRayVisitor visitor;
    Sudoku* sudoku = mRegurgitatedDigit->GetSudoku();
    sudoku->Accept(&visitor);
    ItemXRay* xRay = visitor.GetXRay();

    x += mRegurgitatedDigit->GetWidth() / 3;
    y += mRegurgitatedDigit->GetHeight() / 3;

    int col = static_cast<int>((x - mRegurgitatedDigit->GetWidth() / 2 + mTileSize/2) / mRegurgitatedDigit->GetWidth());
    int row = static_cast<int>((y - mRegurgitatedDigit->GetHeight() / 2) / mRegurgitatedDigit->GetHeight());

    auto overlappingDigit = sudoku->GetDigitAt(col, row);
    if ((overlappingDigit != nullptr) && IsOnBoard(overlappingDigit)) {
        mCanPlaceHere = false;
        return;
    }

    if (mCanPlaceHere) {
        mRegurgitatedDigit->SetLocation(col, row);
        auto digitShared = xRay->PopDigit(mRegurgitatedDigit);
        try {
            sudoku->Add(digitShared);
        } catch (const runtime_error& e) {
            mCanPlaceHere = false;
            return;
        }
    }
}


/**
 * Check if digit is within the sudoku board
 * @param item number being checked
 * @return bool flag
 */
bool RegurgitateVisitor::IsOnBoard(shared_ptr<Item> item)
{
    int colUpperBound = mColLowerBound + 8;
    int rowUpperBound = mRowLowerBound + 8;

    double col = item->GetCol();
    double row = item->GetRow();

    bool isColRange = (mColLowerBound <= col) && (col <= colUpperBound);
    bool isRowRange = (mRowLowerBound <= row) && (row <= rowUpperBound);

    if (isColRange && isRowRange)
    {
        return true;
    }
    else
    {
        return false;
    }
}