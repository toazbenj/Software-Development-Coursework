/**
 * @file Popup.h
 *
 * @author Stefan Lemke, Ethan Egger
 */

#ifndef PROJECT1_SUDOKULIB_POPUP_H
#define PROJECT1_SUDOKULIB_POPUP_H

class PopupManager;

/// Popup drawing function class
class Popup
{
protected:
    Popup(PopupManager *manager, double x, double y, double w, double h);

private:
    /// How much time has elapsed since last popup
    double mSecondsElapsed = 0;
    /// If the popup is visible
    bool mVisible = true;
    /// Where the popup will go (x position)
    double mXPos;
    /// Where the popup will go (y position)
    double mYPos;
    /// How big the popup is (width)
    double mWidth;
    /// How big the popup is (height)
    double mHeight;
    /// Pointer to instance of PopupManager
    PopupManager *mManager;

public:
    /**
     * Draw the popup
     * @param graphics Context on which to draw
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) {}

    /**
     * Getter for visibility flag
     * @return whether popup is visible
     */
    bool IsVisible() const { return mVisible; }

    void SetVisible(bool);

    /**
     * Getter for x coord
     * @return X Position
     */
    double GetXPos() const { return mXPos; }

    /**
     * Getter for y coord
     * @return Y Position
     */
    double GetYPos() const { return mYPos; }

    /**
     * Setter for y coord
     * @param y New Y Position
     */
    void SetYPos(double y) { mYPos = y; }

    /**
     * Getter for width
     * @return Width of popup
     */
    double GetWidth() const { return mWidth; }

    /**
     * Getter for height
     * @return Height of popup
     */
    double GetHeight() const { return mHeight; }

    /**
     * Getter for popup manager
     * @return Manager that owns this popup
     */
    PopupManager* GetManager() const { return mManager; }

    void Instructions(std::shared_ptr<wxGraphicsContext> graphics, int pixelWidth, int pixelHeight, int levelNumber);
    virtual void Update(double elapsed);
    /**
     * Get time passed
     * @return double
     */
    double GetElapsed() {return mSecondsElapsed;}
    void Full(std::shared_ptr<wxGraphicsContext> graphics, double pixelWidth, double pixelHeight);
    void Collision(std::shared_ptr<wxGraphicsContext> graphics, double pixelWidth, double pixelHeight);
    /**
     * Move popup up the screen
     */
    void MovementUpdate() { mYPos -= 10; }
    void WinLoss(std::shared_ptr<wxGraphicsContext> graphics, double pixelWidth, double pixelHeight, bool win);
    void Caught();
};

#endif //PROJECT1_SUDOKULIB_POPUP_H
