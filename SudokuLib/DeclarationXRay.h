/**
 * @file DeclarationXRay.h
 *
 * @author Ethan Egger
 *
 * Class to represent a X-Ray stomach declaration
 */

#ifndef PROJECT1_SUDOKULIB_DECLARATIONXRAY_H
#define PROJECT1_SUDOKULIB_DECLARATIONXRAY_H

#include "Declaration.h"
#include "ItemXRay.h"

/// Inheritance from declaration base class
class DeclarationXRay : public Declaration
{
private:
    /// image for xml entry
    wxString mImage = "";
    /// represented value for xml entry
    double mValue = 0;
    /// How many digits can go into Sparty's stomach
    double mCapacity = 0;
    /// X-Ray image
    std::unique_ptr<wxImage> mDeclarationImage;
    /// X-Ray bitmap
    std::unique_ptr<wxBitmap> mDeclarationBitmap;

public:
    /// Default constructor (disabled)
    DeclarationXRay() = delete;
    /// Copy constructor (disabled)
    DeclarationXRay(const DeclarationXRay &) = delete;
    ~DeclarationXRay();

    DeclarationXRay(wxXmlNode *node);

    /**
     * Make item to add to game
     * @param sudoku ptr to game
     * @param node xml attributes
     * @return xray item ptr
     */
    std::shared_ptr<Item> Create(Sudoku* sudoku, wxXmlNode *node) override
    {
        return std::make_shared<ItemXRay>(sudoku, this);
    }

    void Draw(const std::shared_ptr<wxGraphicsContext>& graphics, double row, double col);
};

#endif //PROJECT1_SUDOKULIB_DECLARATIONXRAY_H
