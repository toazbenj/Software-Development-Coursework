/**
 * @file ItemSparty.h
 * @author Peyton Nagher
 *
 * Item class that manages Sparty gameplay mechanics like eating/regurgitating/headbutting
 */

#ifndef PROJECT1_SUDOKULIB_ITEMSPARTY_H
#define PROJECT1_SUDOKULIB_ITEMSPARTY_H

#include "Item.h"

#include <wx/gdicmn.h>

class DeclarationSparty;

/**
 * Item class describing sparty
 */
class ItemSparty : public Item
{
private:
    /// Point object describing Sparty's target location
    std::unique_ptr<wxRealPoint> mTarget;
    /// Declaration object holding Sparty's details
    DeclarationSparty *mDeclaration;
    /// Check if Sparty is eating
    bool mIsEating;
    /// Check if Sparty is regurgitating
    bool mIsRegurgitating;
    /// Check if Sparty is headbutting
    bool mIsHeadbutting;
    /// Check if Sparty has headbutted just recently
    bool mHasHeadbutt;
    /// Check if Sparty is moving
    bool mIsMoving;
    /// Check if Sparty's mouth is open
    bool mMouthOpen;
    /// Make Sparty's bitmap2 visible
    bool mBitmap2Visible;
    /// A target value for eating/regurgitating
    int mTargetNum;
    /// Amount of time to headbutt
    double mHeadbuttTime = 0;
    /// Amount of time to eat/regurgitate
    double mMoveMouthTime = 0;

public:
    ItemSparty(Sudoku *PSudoku, DeclarationSparty *declaration);
    void MoveMouth(const std::string& option, const int& targetNum = 0);
    void Headbutt();
    void Update(double);
    void SetTarget(double row, double col, bool moving, double pixelWidth, double pixelHeight);
    void Draw(std::shared_ptr<wxGraphicsContext>) override; // add bool mouthOpen
    void XmlLoad(wxXmlNode *) override;
    /**
     * Get movement point
     * @return wx point
     */
    std::unique_ptr<wxRealPoint> GetTarget() { return std::move(mTarget); }
    /**
     * Get image info for sparty
     * @return declaration
     */
    DeclarationSparty *GetDeclaration() { return mDeclaration; }
    /**
     * Get eating flag
     * @return bool
     */
    bool GetEating() { return mIsEating; }
    /**
     * Get regurgitating flag
     * @return bool
     */
    bool GetRegurgitating() { return mIsRegurgitating; }
    /**
     * Get headbutting flag
     * @return bool
     */
    bool GetHeadbutting() { return mIsHeadbutting; }
    /**
     * Overridden accept visitor
     * @param visitor acting on sparty
     */
    void Accept(Visitor* visitor)override{};
};

#endif //PROJECT1_SUDOKULIB_ITEMSPARTY_H
