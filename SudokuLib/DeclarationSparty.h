/**
 * @file DeclarationSparty.h
 *
 * @author Peyton Nagher, Ethan Egger
 *
 * Declaration class that holds specific values for Sparty
 */

#ifndef PROJECT1_SUDOKULIB_DECLARATIONSPARTY_H
#define PROJECT1_SUDOKULIB_DECLARATIONSPARTY_H

#include "Declaration.h"
#include "ItemSparty.h"

/**
 * Declaration class for Sparty
 */
class DeclarationSparty : public Declaration
{
private:
    /// Width of Sparty image
    int mWidth;
    /// Height of Sparty image
    int mHeight;
    /// Which image is drawn in front (1 or 2)?
    int mFront;
    /// Angle at which head butt motion is performed
    double mHeadPivotAngle;
    /// X position of head butt pivot
    double mHeadPivotX;
    /// Y position of head butt pivot
    double mHeadPivotY;
    /// Angle at which eating motion is performed
    double mMouthPivotAngle;
    /// X position of mouth pivot
    double mMouthPivotX;
    /// Y position of mouth pivot
    double mMouthPivotY;
    /// X offset position from mouse click
    double mTargetX;
    /// Y offset position from mouse click
    double mTargetY;

    /// Sparty head image
    std::shared_ptr<wxImage> mImage1;
    /// Sparty mouth image
    std::shared_ptr<wxImage> mImage2;
    /// Sparty head bitmap
    std::shared_ptr<wxBitmap> mBitmap1;
    /// Sparty mouth bitmap
    std::shared_ptr<wxBitmap> mBitmap2;

public:
    DeclarationSparty(wxXmlNode *node);
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
    /**
     * Get image from declaration
     * @return bitmap of image
     */
    std::shared_ptr<wxBitmap> GetBitmap2() const { return mBitmap2; }

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double row, double col, bool mouthOpen, double moveTime, double eatTime);
    void DrawHead(std::shared_ptr<wxGraphicsContext> graphics, double row, double col);
    void DrawMouth(std::shared_ptr<wxGraphicsContext> graphics, double row, double col);
    std::shared_ptr<Item> Create(Sudoku* sudoku, wxXmlNode *node) override;

    /**
     * Get size of image
     * @return double of size
     */
    double GetWidth() const override { return mWidth; }
    /**
     * Get size of image
     * @return double of size
     */
    double GetHeight() const override { return mHeight; }
    /**
     * Get number flag for front image
     * @return int
     */
    int GetFront() const { return mFront; }
    /**
     * Get angle of head tilt for headbutt
     * @return double
     */
    double GetHeadPivotAngle() const { return mHeadPivotAngle; }
    /**
     * Get translation of head during headbutt
     * @return double x coord
     */
    double GetHeadPivotX() const { return mHeadPivotX; }
    /**
     * Get translation of head during headbutt
     * @return double y coord
     */
    double GetHeadPivotY() const { return mHeadPivotY; }
    /**
     * Get angle of mouth tilt for headbutt
     * @return double
     */
    double GetMouthPivotAngle() const { return mMouthPivotAngle; }
    /**
     * Get translation of mouth during headbutt
     * @return double x coord
     */
    double GetMouthPivotX() const { return mMouthPivotX; }
    /**
     * Get translation of mouth during headbutt
     * @return double y coord
     */
    double GetMouthPivotY() const { return mMouthPivotY; }
    /**
     * Set head pivot angle during headbutt
     * @param angle double
     */
    void SetHeadPivotAngle(double angle) { mHeadPivotAngle = angle; }
    /**
   * Set mouth pivot angle during headbutt
   * @param angle double
   */
    void SetMouthPivotAngle(double angle) { mMouthPivotAngle = angle; }
};

#endif //PROJECT1_SUDOKULIB_DECLARATIONSPARTY_H
