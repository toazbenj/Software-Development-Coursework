/**
 * @file ItemDigit.h
 * @author Peyton Nagher, Abhi Rao
 *
 *
 */

#ifndef PROJECT1_SUDOKULIB_ITEMDIGIT_H
#define PROJECT1_SUDOKULIB_ITEMDIGIT_H

#include "Item.h"


class DeclarationDigit;
class Visitor;
/// Base class for digit items
class ItemDigit : public Item
{
private:
    /// Digits Declaration
    DeclarationDigit *mDeclaration;
public:
    /**
     * Constructor
     * @param PSudoku ptr to game
     * @param declaration ptr to image info class
     */
    ItemDigit(Sudoku *PSudoku, DeclarationDigit* declaration) : Item(PSudoku) { mDeclaration = declaration; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    double GetWidth() const override;
    double GetHeight() const override;
    /**
     * Get image info class ptr
     * @return declaration
     */
    DeclarationDigit* GetDeclaration(){return mDeclaration;}
    void Accept(Visitor* visitor) override;
};

#endif //PROJECT1_SUDOKULIB_ITEMDIGIT_H
