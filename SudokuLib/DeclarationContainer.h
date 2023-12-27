/**
 * @file DeclarationContainer.h
 * @author Ethan Egger
 *
 * Container metadata from XML
 */

#ifndef PROJECT1_SUDOKULIB_DECLARATIONCONTAINER_H
#define PROJECT1_SUDOKULIB_DECLARATIONCONTAINER_H

#include "Declaration.h"
#include "ItemContainer.h"

/// Inheritance from declaration base class
class DeclarationContainer : public Declaration
{
private:
    /// image for xml entry
    wxString mImage = "";
    /// represented value for xml entry
    double mValue = 0;
    /// Which image is drawn (cauldron or pumpkin)
    wxString mFront = "";
    /// how many digits the container holds
    int mCapacity = 0;
    /// Container image
    std::unique_ptr<wxImage> mDeclarationImage;
    /// Container bitmap
    std::unique_ptr<wxBitmap> mDeclarationBitmap;
    /// Front image for container
    std::unique_ptr<wxImage> mFrontImage;
    /// Front bitmap for container
    std::unique_ptr<wxBitmap> mFrontBitmap;

public:
    /// Default constructor (disabled)
    DeclarationContainer() = delete;
    /// Copy constructor (disabled)
    DeclarationContainer(const DeclarationContainer &) = delete;
    ~DeclarationContainer();

    DeclarationContainer(wxXmlNode *node);
    /**
      * Make item from declaration
      * @param sudoku ptr to game
      * @param node xml attributes
      * @return background item
      */
    std::shared_ptr<Item> Create(Sudoku* sudoku, wxXmlNode* node) override
    {
        return std::make_shared<ItemContainer>(sudoku, this);
    }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double row, double col) override;
    void DrawFront(std::shared_ptr<wxGraphicsContext> graphics, double row, double col);
    void XmlLoad(wxXmlNode *node) override;
};

#endif //PROJECT1_SUDOKULIB_DECLARATIONCONTAINER_H
