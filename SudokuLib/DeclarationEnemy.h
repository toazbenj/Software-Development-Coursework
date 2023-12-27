/**
 * @file DeclarationEnemy.h
 *
 * @author Abhi Rao
 *
 * Class to represent a enemy declaration, derived from Declaration
 */

#ifndef PROJECT1_SUDOKULIB_DECLARATIONENEMY_H
#define PROJECT1_SUDOKULIB_DECLARATIONENEMY_H

#include "Declaration.h"
#include "ItemEnemy.h"
#include "Item.h"
#include "Sudoku.h"

/// Image info manager class for xml loading
class DeclarationEnemy : public Declaration {
private:
    /// Width of Enemy image
    int mWidth = 0;
    /// Height of Enemy image
    int mHeight = 0;
    /// image for xml entry
    wxString mImage = "";
    /// direction of enemy
    wxString mDirection = "";
    /// Enemy image
    std::unique_ptr<wxImage> mDeclarationImage;
    /// Enemy bitmap
    std::unique_ptr<wxBitmap> mDeclarationBitmap;
    /// X offset position from mouse click
    double mTargetX;
    /// Y offset position from mouse click
    double mTargetY;

public:
    DeclarationEnemy(const DeclarationEnemy &) = delete;
    void XmlLoad(wxXmlNode *node) override;
    DeclarationEnemy(wxXmlNode *node);
    std::shared_ptr<Item> Create(Sudoku *sudoku, wxXmlNode *node) override;

    /**
     * Getter for width
     * @return width of enemy object
     */
    double GetWidth() const override { return mWidth; }

    /**
     * Getter for height
     * @return height of enemy object
     */
    double GetHeight() const override { return mHeight; }
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double row, double col) override;
    /**
     * Get value of click coord for movement
     * @return x coord
     */
    double GetTargetX() const { return mTargetX; }
    /**
     * Get value of click coord for movement
     * @return y coord
     */
    double GetTargetY() const { return mTargetY; }
};

#endif //PROJECT1_SUDOKULIB_DECLARATIONENEMY_H
