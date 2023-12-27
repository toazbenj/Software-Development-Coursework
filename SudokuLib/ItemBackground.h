/**
 * @file ItemBackground.h
 * @author Ethan Egger
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_ITEMBACKGROUND_H
#define PROJECT1_SUDOKULIB_ITEMBACKGROUND_H

#include "Item.h"

class DeclarationBackground;
/// Playing area image
class ItemBackground : public Item
{
private:
    /// Declaration object for background
    DeclarationBackground *mDeclaration;

public:
    ///constructor
    ItemBackground(Sudoku *sudoku, DeclarationBackground *declaration);

    void Draw(std::shared_ptr<wxGraphicsContext>) override;

    /**
     * Accept a visitor object
     * @param visitor Visitor to be accepted
     */
    void Accept(Visitor* visitor)override{} ;
};

#endif //PROJECT1_SUDOKULIB_ITEMBACKGROUND_H
