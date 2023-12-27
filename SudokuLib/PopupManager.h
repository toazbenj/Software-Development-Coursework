/**
 * @file PopupManager.h
 *
 * @author Stefan Lemke, Ethan Egger
 *
 * Class responsible for initializing and storing Popups
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_POPUPMANAGER_H
#define ACTIONSUDOKU_SUDOKULIB_POPUPMANAGER_H

#include "Popup.h"
#include "PopupInstructions.h"
#include "PopupFull.h"
#include "PopupWinLoss.h"
#include "PopupCaught.h"

#include <memory>
#include <vector>

class Sudoku;

/**
 * Class for managing Popups
 */
class PopupManager
{
private:
    /// Collection of popups stored in the system
    std::vector<std::shared_ptr<Popup>> mPopups;
    /// Pointer to sudoku object
    Sudoku* mSudoku;
    /// Popup for level instructions
    std::shared_ptr<PopupInstructions> mInstructions;
    /// Popup for Win/Loss state
    std::shared_ptr<PopupWinLoss> mWinLoss;
    /// Popup for if player is caught
    std::shared_ptr<PopupCaught> mCaught;

public:
    PopupManager(Sudoku* sudoku);
    /**
     * Getter for sudoku object
     * @return Sudoku instanct that owns this manager
     */
    Sudoku* GetSudoku() const { return mSudoku; }
    void Load();
    void AddFull();
    void AddCollision();
    void RemovePopup(Popup*);
    /**
     * Getter for instructions popup
     * @return instructions popup associated with this object
     */
    std::shared_ptr<PopupInstructions> GetInstructions() const { return mInstructions; }
    /**
     * Getter for Win/Loss popup
     * @return Win/Loss popup associtaed with this object
     */
    std::shared_ptr<PopupWinLoss> GetWinLoss() const { return mWinLoss; }
    /**
     * Getter for caught popup
     * @return
     */
    std::shared_ptr<PopupCaught> GetCaught() const { return mCaught; }
    void Update(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //ACTIONSUDOKU_SUDOKULIB_POPUPMANAGER_H
