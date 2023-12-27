/**
 * @file ItemDigitGiven.h
 * @author Peyton Nagher
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_ITEMDIGITGIVEN_H
#define PROJECT1_SUDOKULIB_ITEMDIGITGIVEN_H

#include "ItemDigit.h"

/// Fixed digits on sudoku board
class ItemDigitGiven : public ItemDigit
{
public:
    /**
      * Constructor
      * @param PSudoku ptr to game
      * @param declaration ptr to image info class
      */
    ItemDigitGiven(Sudoku *PSudoku, DeclarationDigit *declaration) : ItemDigit(PSudoku, declaration) {}

};

#endif //PROJECT1_SUDOKULIB_ITEMDIGITGIVEN_H
