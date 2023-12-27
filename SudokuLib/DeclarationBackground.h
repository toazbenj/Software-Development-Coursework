/**
 * @file DeclarationBackground.h
 *
 * @author Ethan Egger
 *
 * Image metadata from XML
 */

#ifndef PROJECT1_SUDOKULIB_DECLARATIONBACKGROUND_H
#define PROJECT1_SUDOKULIB_DECLARATIONBACKGROUND_H

#include "Declaration.h"
#include "ItemBackground.h"
#include <wx/graphics.h>

/// Image info manager class for xml loading
class DeclarationBackground : public Declaration
{
private:
    /// image for xml entry
    wxString mImage = "";
    /// Background image
    std::unique_ptr<wxImage> mDeclarationImage;
    /// Background bitmap
    std::unique_ptr<wxBitmap> mDeclarationBitmap;

public:
    DeclarationBackground() = delete;
    DeclarationBackground(const DeclarationBackground &) = delete;
    ~DeclarationBackground();

    DeclarationBackground(wxXmlNode *node);

    /**
     * Make item from declaration
     * @param sudoku ptr to game
     * @param node xml attributes
     * @return background item
     */
    std::shared_ptr<Item> Create(Sudoku* sudoku, wxXmlNode* node) override
    {
        return std::make_shared<ItemBackground>(sudoku, this);
    }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double row, double col) override;
    void XmlLoad(wxXmlNode *node) override;
};

#endif //PROJECT1_SUDOKULIB_DECLARATIONBACKGROUND_H
