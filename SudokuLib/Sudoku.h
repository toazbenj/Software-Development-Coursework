/**
 * @file Sudoku.h
 * @author Peyton Nagher, Ben Toaz
 *
 * Class to represent the Sudoku game and its virtual pixels
 */

#ifndef PROJECT1_SUDOKULIB_SUDOKU_H
#define PROJECT1_SUDOKULIB_SUDOKU_H

#include "Item.h"
#include "ScoreBoard.h"
#include "ItemSparty.h"
#include "ItemEnemy.h"
#include "ItemDigitMovable.h"
#include "Popup.h"
#include "PopupManager.h"
#include <memory>
#include <wx/graphics.h>
#include <random>

/**
 * Class describing a game of Sudoku
 *
 * Stores items such as digits, containers, and sparty
 */
class Sudoku
{
private:
    /// Collection of game item objects
    std::vector<std::shared_ptr<Item>> mItems = std::vector<std::shared_ptr<Item>>();
    /// Pointer to Sparty Object
    std::shared_ptr<ItemSparty> mSparty = nullptr;
    /// Pointer to Enemy Object
    std::shared_ptr<ItemEnemy> mEnemy = nullptr;
    /// pointer to Level object
    std::shared_ptr<Level> mLevel = nullptr;
    /// ScoreBoard creation
    std::shared_ptr<ScoreBoard> mScoreBoard = nullptr;
    /// Pointer to popup manager
    std::shared_ptr<PopupManager> mPopupManager;
    /// Conversion factor between regular coords and virtual pixel coords
    double mScale = 0;
    /// Added to coords to put origin at center top of screen
    double mXOffset = 0;
    /// Same, but usually just 0
    double mYOffset = 0;
    /// Timer member variable
    int mTimer = 0;
    /// What level is loaded
    int mLevelNumber;
    /// Item loaded from XML
    void XmlItem(wxXmlNode *node);
    /// boolean representing if a new level has been loaded
    bool mNewLevel = false;
    /// Random number generator
    std::mt19937 mRandom;
    /// Flag for pausing all game mechanics
    bool mFreeze;

public:
    Sudoku(const Sudoku &) = delete;
    void operator=(const Sudoku &) = delete;
    Sudoku();
    void Add(std::shared_ptr<Item>& item);
    std::shared_ptr<ItemDigitMovable> PopDigit(ItemDigitMovable*);
    void Load(const wxString &filename, const int &levelNum);
    void Clear();
    void MoveSpartyFront();
    std::shared_ptr<Item> HitTest(double x, double y);

    /**
     * Sets frozen flag
     */
    void Freeze() { mFreeze = true; }

    /**
     * Unsets frozen flag
     */
    void Unfreeze() { mFreeze = false; }

    /**
     * Getter for sudoku's frozen flag
     * @return whether sudoku is frozen
     */
    bool IsFrozen() const { return mFreeze; }
    void OnDraw(std::shared_ptr<wxGraphicsContext>& graphics, const int& width, const int& height);
    void OnLeftDown(const int& x,const int& y);
    void OnSpaceDown();
    void OnBDown();
    void OnNumKeyDown(const int& targetNum);
    void Update(const double& elapsed);
    std::shared_ptr<Item> GetDigitAt(int, int);
    void Accept(Visitor *visitor);
    void CheckSolution(const std::vector<int>& currentAnswer);
    void AdvanceLevel(bool win);
    void Solve();
    void MoveEnemyFront();

    /**
     * Setter for sparty
     * @param sparty pointer to sparty object
     */
    void SetSparty(std::shared_ptr<ItemSparty>& sparty) { mSparty = sparty; }


    /**
     * Getter for sparty
     * @return Player avatar that eats and regurgitates digits
     */
    std::shared_ptr<ItemSparty> GetSparty() { return mSparty; }

    /**
     * Setter for the enemy object
     * @param enemy Item that chases sparty to empty its xray
     */
    void SetEnemy(std::shared_ptr<ItemEnemy>& enemy) { mEnemy = enemy; }

    /**
     * Setter for the new level flag
     * @param status Whether a new level is loaded
     */
    void SetNewLevel(bool status) { mNewLevel = status; }

    /**
     * Getter for the level object
     * @return The current level loaded into sudoku
     */
    std::shared_ptr<Level> GetLevel() { return mLevel; }

    /**
     * Getter for the level number
     * @return The number of the current level
     */
    int GetLevelNum() const { return mLevelNumber; }

    /**
     * Getter for use with random numbers
     * @return random number seed
     */
    std::mt19937 &GetRandom() { return mRandom; }

    /**
     * Getter for the collection of Items
     * @return vector of Sudoku's items
     */
    std::vector<std::shared_ptr<Item>>& GetItems() { return mItems; }

    /**
     * Getter for the scoreboard object
     * @return The scoreboard for sudoku
     */
    std::shared_ptr<ScoreBoard> GetScoreBoard(){return mScoreBoard;}

    /**
     * Getter for popup manager
     * @return the popup manager storing sudoku's popups
     */
    std::shared_ptr<PopupManager> GetPopupManager() const { return mPopupManager; }

};


#endif //PROJECT1_SUDOKULIB_SUDOKU_H
