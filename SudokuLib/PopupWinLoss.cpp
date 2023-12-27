/**
 * @file PopupWinLoss.cpp
 *
 * @author Stefan Lemke, Ethan Egger
 */

#include "pch.h"
#include "PopupWinLoss.h"
#include "PopupManager.h"
#include "Sudoku.h"

#include <wx/graphics.h>

/**
 * Constructor
 *
 * @param manager
 * @param x
 * @param y
 */
PopupWinLoss::PopupWinLoss(PopupManager *manager, double x, double y) : Popup(manager, x, y, 0, 0)
{
    SetVisible(false);
}

/**
 * Start the popup to display the correct message
 *
 * @param win whether the player won the game
 */
void PopupWinLoss::Initialize(bool win)
{
    mWin = win;
    SetVisible(true);
    GetManager()->GetSudoku()->Freeze();
}

/**
 * Draws the win/loss popup
 *
 * @param graphics context for drawing
 */
void PopupWinLoss::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!IsVisible())
    {
        return;
    }

    wxFont bigFont(wxSize(0, 100),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(10, 171, 29));
    double wid, hit;
    if (mWin)
    {
        graphics->GetTextExtent(L"Level Complete!", &wid, &hit);
        graphics->DrawText(L"Level Complete!", GetXPos() - wid/2, GetYPos() - hit/2);
    }
    else
    {
        graphics->GetTextExtent(L"Incorrect!", &wid, &hit);
        graphics->DrawText(L"Incorrect!", GetXPos() - wid/2, GetYPos() - hit/2);
    }
}

/**
 * Updates the status of the game based on win/loss popup
 *
 * @param elapsed
 */
void PopupWinLoss::Update(double elapsed)
{
    if (IsVisible())
    {
        Popup::Update(elapsed);

        if (GetElapsed() > 3)
        {
            GetManager()->GetSudoku()->Unfreeze();
            GetManager()->GetSudoku()->AdvanceLevel(mWin);
        }
    }
}
