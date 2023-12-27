/**
 * @file PopupInstructions.h
 *
 * @author Stefan Lemke, Ethan Egger
 *
 * Popup class describing game instructions
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_POPUPINSTRUCTIONS_H
#define ACTIONSUDOKU_SUDOKULIB_POPUPINSTRUCTIONS_H

#include "Popup.h"

/**
 * Class for displaying Instructions popup
 */
class PopupInstructions : public Popup
{
public:
    /**
     * Constructor for Instructions Popup
     * @param manager ptr to manager object
     * @param x X Position of Popup
     * @param y Y Position of Popup
     */
    PopupInstructions(PopupManager* manager, double x, double y) : Popup(manager, x, y, 700, 319) {}
    void Draw(std::shared_ptr<wxGraphicsContext>) override;
    void Update(double elapsed) override;
};

#endif //ACTIONSUDOKU_SUDOKULIB_POPUPINSTRUCTIONS_H
