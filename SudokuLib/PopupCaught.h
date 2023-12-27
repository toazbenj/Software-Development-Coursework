/**
 * @file PopupCaught.h
 * @author Stefan Lemke
 *
 * Popup class describing caught state
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_POPUPCAUGHT_H
#define ACTIONSUDOKU_SUDOKULIB_POPUPCAUGHT_H

#include "Popup.h"

/**
 * Class for describing caught popup
 */
class PopupCaught : public Popup
{
private:
    /// Indicates at what time Sparty was caught by Dr. Owen
    double mTimeCaught;
public:
    PopupCaught(PopupManager* manager, double x, double y);
    void Draw(std::shared_ptr<wxGraphicsContext>) override;
    void Update(double elapsed) override;
    void Initialize(double elapsed);

};

#endif //ACTIONSUDOKU_SUDOKULIB_POPUPCAUGHT_H
