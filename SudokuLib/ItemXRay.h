/**
 * @file ItemXRay.h
 * @author Peyton Nagher
 *
 * Class that represents Sparty's stomach
 */

#ifndef PROJECT1_SUDOKULIB_ITEMXRAY_H
#define PROJECT1_SUDOKULIB_ITEMXRAY_H

#include "Item.h"
#include "Declaration.h"
#include "ItemContainer.h"

class DeclarationXRay;
/// Visual for sparty's guts
class ItemXRay : public Item
{
private:
    /// Declaration object holding X-Ray's details
    DeclarationXRay *mDeclaration;
    /// Vector of items that are in the X-Ray
    std::vector<std::shared_ptr<Item>> mItems;

public:
    ItemXRay(Sudoku *PSudoku, DeclarationXRay* declaration);
    ItemXRay(const ItemXRay &) = delete;
    void operator=(const ItemXRay &) = delete;
    void Draw(std::shared_ptr<wxGraphicsContext>) override;
    void Accept(Visitor* visitor)override;
    void ContentsAccept(Visitor* visitor);
    void AddDigit(std::shared_ptr<Item> digit);
    /**
     * Getter for the size of XRay's collection of digits
     * @return number of digits in xray
     */
    auto GetNumDigits() const { return mItems.size(); }
    std::shared_ptr<Item> PopDigit(ItemDigitMovable* digit);
    void ReleaseDigits();
};

#endif //PROJECT1_SUDOKULIB_ITEMXRAY_H
