/**
 * @file DeclarationDigit.h
 *
 * @author Ethan Egger, Peyton Nagher
 *
 * Digit info from XML
 */

#ifndef PROJECT1_SUDOKULIB_DECLARATIONDIGIT_H
#define PROJECT1_SUDOKULIB_DECLARATIONDIGIT_H

#include "Declaration.h"
#include "ItemDigitMovable.h"

/// Inheritance from declaration base class
class DeclarationDigit : public Declaration
{
private:
    /// image for xml entry
    wxString mImage = "";
    /// represented value for xml entry
    int mValue = 0;
    /// Digit image
    std::unique_ptr<wxImage> mDeclarationImage;
    /// Digit bitmap
    std::unique_ptr<wxBitmap> mDeclarationBitmap;

public:
    DeclarationDigit() = delete;
    DeclarationDigit(const DeclarationDigit &) = delete;
    ~DeclarationDigit();

    DeclarationDigit(wxXmlNode *node);

    std::shared_ptr<Item> Create(Sudoku* sudoku, wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double row, double col) override;
    void XmlLoad(wxXmlNode *node) override;

    /**
     * Get value of the digit being made
     * @return int value
     */
    int GetValue() const {return mValue;}
};

#endif //PROJECT1_SUDOKULIB_DECLARATIONDIGIT_H
