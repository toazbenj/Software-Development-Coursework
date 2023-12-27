/**
 * @file ItemContainer.h
 *
 * @author Peyton Nagher
 *
 * Class to represent a Cauldron or Pumpkin item
 */

#ifndef PROJECT1_SUDOKULIB_ITEMCONTAINER_H
#define PROJECT1_SUDOKULIB_ITEMCONTAINER_H

#include "Item.h"
#include "ItemDigitMovable.h"

class DeclarationContainer;
/// Base class for container items
class ItemContainer : public Item
{
private:
    /// some container declaration for values
    DeclarationContainer *mDeclaration;
    /// Items held by container
    std::vector<std::shared_ptr<Item>> mItems;

public:
    /**
     * Constructor
     * @param PSudoku ptr to game
     * @param declaration ptr to image info class
     */
    ItemContainer(Sudoku *PSudoku, DeclarationContainer* declaration) : Item(PSudoku) { mDeclaration = declaration; }

    void XmlLoad(wxXmlNode *) override;
    double GetWidth() const override;
    double GetHeight() const override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Accept(Visitor* visitor) override;
    void ReleaseDigits();
    void AddDigit(std::shared_ptr<Item>);
    // void RemoveDigit(ItemDigit*);
};

#endif //PROJECT1_SUDOKULIB_ITEMCONTAINER_H
