/**
 * @file SolveVisitor.h
 * @author Ben Toaz
 *
 * Visitor to auto solve level
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_SOLVEVISITOR_H
#define ACTIONSUDOKU_SUDOKULIB_SOLVEVISITOR_H

#include "Visitor.h"
#include "ItemDigit.h"
#include "ItemDigitMovable.h"

/// Visitor to move digits to sudoku board
class SolveVisitor: public Visitor
{
private:
    /// value to check against
    int mValue = 10;
    /// value to represent the target row
    int mCurrentRow = 100;
    /// value to represent the target column
    int mCurrentCol = 100;
    /// boolean to see if a cell is full
    bool mIsSquareFull = false;

public:
    SolveVisitor(int, int, int);
    virtual void VisitDigit(ItemDigit *digit) override;
    virtual void VisitDigitMovable(ItemDigitMovable* digit) override;
};

#endif //ACTIONSUDOKU_SUDOKULIB_SOLVEVISITOR_H
