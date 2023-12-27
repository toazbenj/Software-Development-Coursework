/**
 * @file PopupWinLoss.h
 * @author Stefan Lemke, Ethan Egger
 *
 * Popup Class for Win/Loss state
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_POPUPWINLOSS_H
#define ACTIONSUDOKU_SUDOKULIB_POPUPWINLOSS_H

#include "Popup.h"

/**
 * Class describing Win/Loss popup
 */
class PopupWinLoss : public Popup
{
private:
    /// Check if the player won the game
    bool mWin;

public:
    PopupWinLoss(PopupManager* manager, double x, double y);
    void Initialize(bool win);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed) override;
};

#endif //ACTIONSUDOKU_SUDOKULIB_POPUPWINLOSS_H
