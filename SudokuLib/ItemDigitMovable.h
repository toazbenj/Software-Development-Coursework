/**
 * @file ItemDigitMovable.h
 * @author Peyton Nagher
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_ITEMDIGITMOVEABLE_H
#define PROJECT1_SUDOKULIB_ITEMDIGITMOVEABLE_H

#include "ItemDigit.h"

/// Interactive digits
class ItemDigitMovable : public ItemDigit
{
private:
    /// flag for being placed in board position
    bool mIsMoved = false;

public:
    /**
      * Constructor
      * @param PSudoku ptr to game
      * @param declaration ptr to image info class
      */
    ItemDigitMovable(Sudoku *PSudoku, DeclarationDigit *declaration) : ItemDigit(PSudoku, declaration) {}
    /**
     * Get movement flag
     * @return bool
     */
    bool IsMoved(){return mIsMoved;}
    /**
     * Set movement flag
     * @param flag whether item has been moved
     */
    void SetMoved(bool flag){mIsMoved = flag;}
    void Accept(Visitor *visitor) override;
};

#endif //PROJECT1_SUDOKULIB_ITEMDIGITMOVEABLE_H
