/**
 * @file RegurgitateVisitor.h
 *
 * @author Ben Toaz, Peyton Nagher
 *
 * Similar to eat visitor for sudoku during sparty move mouth, but in reverse.
 */

#ifndef PROJECT1_SUDOKULIB_REGURGITATEVISITOR_H
#define PROJECT1_SUDOKULIB_REGURGITATEVISITOR_H

#include "Visitor.h"
#include "ItemXRay.h"
#include "ItemSparty.h"

/// Inheritance from visitor class
class RegurgitateVisitor: public Visitor
{
private:
    /// digit being spit back
    ItemDigitMovable* mRegurgitatedDigit = nullptr;
    /// flag for stacking
    bool mCanPlaceHere;
    /// int value of digit
    int mTargetVal;
    /// size of virtual pixel tiles
    int mTileSize;
    /// sudoku board upper left coord
    int mColLowerBound = 100;
    /// sudoku board upper left coord
    int mRowLowerBound = 100;

public:
    RegurgitateVisitor(int value, int size, std::vector<int> boardBounds);
    void VisitDigitMovable(ItemDigitMovable*) override;
    void SendToGameBoard(double, double);
    /**
     * Get digit being spat out
     * @return moveable digit ptr
     */
    ItemDigitMovable* GetDigit() const { return mRegurgitatedDigit; }
    /**
     * Get placement flag
     * @return bool
     */
    bool GetCanPlaceHere(){return mCanPlaceHere;}
    bool IsOnBoard(std::shared_ptr<Item> item);
};

#endif //PROJECT1_SUDOKULIB_REGURGITATEVISITOR_H
