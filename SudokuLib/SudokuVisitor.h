/**
 * @file SudokuVisitor.h
 *
 * @author Ben Toaz
 *
 * Visitor class for the Sudoku board
 */

#ifndef PROJECT1_SUDOKULIB_SUDOKUVISITOR_H
#define PROJECT1_SUDOKULIB_SUDOKUVISITOR_H

#include "Visitor.h"
#include "ItemDigit.h"
#include "ItemDigitMovable.h"

/**
 * Visitor class for determining current state of board
 *
 * Generates a vector representing current solution
 */
class SudokuVisitor: public Visitor
{
private:
    /// Vector of int's that represents the solution for a Sudoku level
    std::vector<int> mAnswer;
    /// Bounds for the board visitor
    int mColLowerBound = 100;
    /// sudoku board upper left coord
    int mRowLowerBound = 100;

public:
    SudokuVisitor(std::vector<int> boardBounds);

    /**
     * Getter for the current board's state
     * @return Answer on the board
     */
    std::vector<int> GetAnswer(){return mAnswer;}
    virtual void VisitDigit(ItemDigit* digit) override;
    virtual void VisitDigitMovable(ItemDigitMovable* digit) override;
    bool IsOnBoard(ItemDigit *digit);
};

#endif //PROJECT1_SUDOKULIB_SUDOKUVISITOR_H
