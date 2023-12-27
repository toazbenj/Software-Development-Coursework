/**
 * @file SudokuVisitor.cpp
 * @author Ben Toaz
 */

#include "pch.h"
#include "SudokuVisitor.h"
#include "ItemDigit.h"
#include "DeclarationDigit.h"
#include "Sudoku.h"

using namespace std;

/**
 * Visitor to check the Sudoku board
 *
 * @param boardBounds X & Y dimensions of the Sudoku board
 */
SudokuVisitor::SudokuVisitor(std::vector<int> boardBounds)
{
    mAnswer.resize(81);
    fill(mAnswer.begin(), mAnswer.end(),10);
    mRowLowerBound = boardBounds[0];
    mColLowerBound = boardBounds[1];
}

/**
 * Find all the digits, check if they are on the board, snap to position and get value
 *
 * @param digit the number item we are gathering info from
 */
void SudokuVisitor::VisitDigit(ItemDigit *digit)
{
    double col = digit->GetCol();
    double row = digit->GetRow();
    int index = (col-mColLowerBound)+(row-mRowLowerBound)*9;
    mAnswer[index] = digit->GetDeclaration()->GetValue();
}

/**
 * Visitor for a movable digit
 *
 * @param digit
 */
void SudokuVisitor::VisitDigitMovable(ItemDigitMovable *digit)
{
    if (IsOnBoard(digit))
    {
        double oldCol = digit->GetCol();
        double oldRow = digit->GetRow();
        int newCol = (int) oldCol;
        int newRow = (int) oldRow;
        digit->SetLocation(newCol, newRow);

        // calculate answer index from rows and columns
        int index = (newCol-mColLowerBound)+(newRow-mRowLowerBound)*9;
        // assign value to that index
        mAnswer[index] = digit->GetDeclaration()->GetValue();
    }
}

/**
 * Check if digit is within the sudoku board
 * @param digit number being checked
 * @return bool flag
 */
bool SudokuVisitor::IsOnBoard(ItemDigit *digit)
{
    int colUpperBound = mColLowerBound + 8;
    int rowUpperBound = mRowLowerBound + 8;

    double col = digit->GetCol();
    double row = digit->GetRow();

    bool isColRange = (mColLowerBound <= col) && (col <= colUpperBound);
    bool isRowRange = (mRowLowerBound <= row) && (row <= rowUpperBound);

    if(isColRange && isRowRange)
    {
        return true;
    }
    else
    {
        return false;
    }
}
