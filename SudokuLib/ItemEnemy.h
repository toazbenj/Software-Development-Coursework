/**
 * @file ItemEnemy.h
 * @author Abhi Rao
 *
 * Class that represents our enemy Dr. Owen
 */

#ifndef PROJECT1_SUDOKULIB_ITEMENEMY_H
#define PROJECT1_SUDOKULIB_ITEMENEMY_H

#include "Item.h"
#include <wx/gdicmn.h>
#include <wx/sound.h>

class DeclarationEnemy;
class DeclarationSparty;
class DeclarationXRay;
class Visitor;
///Object to chase sparty
class ItemEnemy : public Item {
private:
    /// Declaration object holding enemy's details
    DeclarationEnemy *mDeclaration;
    /// Declaration object holding Sparty's details
    DeclarationSparty *mSpartyDeclaration;
    /// Declaration object holding XRay's details
    DeclarationSparty *mXrayDeclaration;
    /// Point object describing Enemy's target location
    std::unique_ptr<wxRealPoint> mTarget;
    /// Boolean to check if enemy is moving
    bool mIsMoving;
    /// Pointer to sound object
    std::unique_ptr<wxSound> mSound;
public:
    ItemEnemy(Sudoku *PSudoku, DeclarationEnemy *declaration);
    double GetWidth() const override;
    double GetHeight() const override;
    void Update(double);
    /**
     *
     * @return declaration of enemy
     */
    DeclarationEnemy* GetDeclaration() { return mDeclaration; }
    void SetTarget(double row, double col, bool moving, double pixelWidth, double pixelHeight);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void XmlLoad(wxXmlNode *) override;

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(Visitor* visitor) override {};
};

#endif //PROJECT1_SUDOKULIB_ITEMENEMY_H
