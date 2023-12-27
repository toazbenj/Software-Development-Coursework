/**
 * @file PopupCollision.h
 *
 * @author Stefan Lemke, Ethan Egger
 *
 * Popup class for occupied tiles
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_POPUPCOLLISION_H
#define ACTIONSUDOKU_SUDOKULIB_POPUPCOLLISION_H

#include "Popup.h"

/// Draw manager for messages
class PopupCollision : public Popup
{
public:
    /**
     * Constructor
     * @param manager
     * @param x
     * @param y
     */
    PopupCollision(PopupManager* manager, double x, double y) : Popup(manager, x, y, 500, 50) {}
    void Draw(std::shared_ptr<wxGraphicsContext>) override;
    void Update(double elapsed) override;
};

#endif //ACTIONSUDOKU_SUDOKULIB_POPUPCOLLISION_H
