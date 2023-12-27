/**
 * @file PopupManager.cpp
 * @author Ethan Egger
 */

#include "pch.h"
#include "PopupManager.h"
#include "PopupInstructions.h"
#include "PopupCollision.h"
#include "Sudoku.h"

#include <algorithm>

using namespace std;

/**
 * Constructor
 *
 * @param sudoku Sudoku object that owns this manager
 */
PopupManager::PopupManager(Sudoku* sudoku) : mSudoku(sudoku) {}

/**
 * Loads in popups for sudoku
 */
void PopupManager::Load()
{
    double tileWid = mSudoku->GetLevel()->GetTileWidth();
    double tileHit = mSudoku->GetLevel()->GetTileHeight();

    double width = mSudoku->GetLevel()->GetWidth() * tileWid;
    double height = mSudoku->GetLevel()->GetHeight() * tileHit;

    mInstructions = make_shared<PopupInstructions>(this, width / 2, height / 2);
    mWinLoss = make_shared<PopupWinLoss>(this, width / 2, height / 2);
    mCaught = make_shared<PopupCaught>(this, width / 2, height / 2);
}

/**
 * Add a popup to manager's collection
 *
 */
void PopupManager::AddFull()
{
    double tileWid = mSudoku->GetLevel()->GetTileWidth();
    double tileHit = mSudoku->GetLevel()->GetTileHeight();

    double width = mSudoku->GetLevel()->GetWidth() * tileWid;
    double height = mSudoku->GetLevel()->GetHeight() * tileHit;

    auto popup = make_shared<PopupFull>(this, width / 2, height);
    mPopups.push_back(popup);
}

/**
 * Adds a collision popup to manager's collection
 */
void PopupManager::AddCollision()
{
    double tileWid = mSudoku->GetLevel()->GetTileWidth();
    double tileHit = mSudoku->GetLevel()->GetTileHeight();

    double width = mSudoku->GetLevel()->GetWidth() * tileWid;
    double height = mSudoku->GetLevel()->GetHeight() * tileHit;

    auto popup = make_shared<PopupCollision>(this, width / 2, height);
    mPopups.push_back(popup);
}

/**
 * Removes popup from manager's collection
 *
 * @param popup
 */
void PopupManager::RemovePopup(Popup *popup)
{
    for(auto itr = mPopups.begin(); itr != mPopups.end(); ++itr)
    {
        if(itr->get() == popup)
        {
            mPopups.erase(itr);
            return;
        }
    }
}

/**
 * Update all of the popups
 *
 * @param elapsed time since last update
 */
void PopupManager::Update(double elapsed)
{
    mInstructions->Update(elapsed);
    mWinLoss->Update(elapsed);
    mCaught->Update(elapsed);

    vector<shared_ptr<Popup>> toRemove;
    for(auto popup : mPopups)
    {
        popup->Update(elapsed);
        if(popup->GetYPos() + popup->GetHeight() < 0)
        {
            toRemove.push_back(popup);
        }
    }
    for(auto popup : toRemove)
    {
        auto pos = find(mPopups.begin(), mPopups.end(), popup);
        mPopups.erase(pos);
    }
}

/**
 * Draw all popups
 *
 * @param graphics Context on which to draw
 */
void PopupManager::Draw(shared_ptr<wxGraphicsContext> graphics)
{
    mInstructions->Draw(graphics);
    mWinLoss->Draw(graphics);
    mCaught->Draw(graphics);

    for(auto popup : mPopups)
    {
        popup->Draw(graphics);
    }
}
