/**
 * @file SolveVisitor.cpp
 * @author Ben Toaz
 *
 * Visitor to move digits during auto solve
 */

#include "pch.h"
#include "SolveVisitor.h"
#include "ItemDigitMovable.h"
#include "ItemDigit.h"
#include "DeclarationDigit.h"

using namespace std;

/**
 * Visitor to check a solution for a cell on the board
 *
 * @param row
 * @param col
 * @param value
 */
SolveVisitor::SolveVisitor(int row, int col, int value)
{
    mCurrentRow = row;
    mCurrentCol = col;
    mValue = value;
}

/**
 * Visitor to check a movable digit
 *
 * @param digit
 */
void SolveVisitor::VisitDigitMovable(ItemDigitMovable *digit)
{
    if (((digit->GetDeclaration()->GetValue()) == mValue) && (!mIsSquareFull)&&(!digit->IsMoved()))
    {
        digit->SetCol(mCurrentCol);
        digit->SetRow(mCurrentRow);
        mIsSquareFull = true;
        digit->SetMoved(true);
    }
}

/**
 * Visitor to see if a digit is in a specific cell
 *
 * @param digit
 */
void SolveVisitor::VisitDigit(ItemDigit *digit)
{
    if ((digit->GetCol()==mCurrentCol) && (digit->GetRow() == mCurrentRow))
    {
        mIsSquareFull = true;
    }
}
