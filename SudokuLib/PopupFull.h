/**
 * @file PopupFull.h
 *
 * @author Stefan Lemke, Ethan Egger
 *
 * Popup class for when sparty is full
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_POPUPFULL_H
#define ACTIONSUDOKU_SUDOKULIB_POPUPFULL_H

#include "Popup.h"

/**
 * Class describing the "full" popup
 */
class PopupFull : public Popup
{
public:
    /**
     * Constructor
     * @param manager
     * @param x
     * @param y
     */
    PopupFull(PopupManager* manager, double x, double y) : Popup(manager, x, y, 180, 50) {}
    void Draw(std::shared_ptr<wxGraphicsContext>) override;
    void Update(double elapsed) override;
};

#endif //ACTIONSUDOKU_SUDOKULIB_POPUPFULL_H
