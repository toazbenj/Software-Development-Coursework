/**
 * @file PopupCaught.cpp
 * @author Stefan Lemke
 *
 * Popup class describing caught state
 *
 */
#include "pch.h"
#include "PopupCaught.h"
#include "PopupManager.h"
#include "Sudoku.h"
#include <wx/graphics.h>


/**
 * Constructor
 * @param manager popup manager to which this belongs
 * @param x coordinate of game board
 * @param y coordinate of game board
 */
PopupCaught::PopupCaught(PopupManager *manager, double x, double y) : Popup(manager, x, y, 0, 0)
{
    SetVisible(false);
}

/**
 * Initialize the 'caught' popup
 * @param elapsed time when caught
 */
void PopupCaught::Initialize(double elapsed)
{
    mTimeCaught = elapsed;
    SetVisible(true);
}

/**
 * Draw the "caught" popup
 *
 * @param graphics context on which to draw
 */
void PopupCaught::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!IsVisible())
    {
        return;
    }

    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(wxNullGraphicsPen);
    graphics->DrawRectangle(GetXPos()-550, GetYPos()-75, 1100, 150);

    wxFont bigFont(wxSize(0, 100),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(10, 171, 29));
    double wid, hit;
    graphics->GetTextExtent(L"You've Been Caught!", &wid, &hit);
    graphics->DrawText(L"You've Been Caught!", GetXPos() - wid/2, GetYPos() - hit/2);

}

/**
 * Function to spawn and de-spawn the instruction popup
 *
 * @param elapsed
 */
void PopupCaught::Update(double elapsed)
{
    Popup::Update(elapsed);

    if (IsVisible() && (GetElapsed() - mTimeCaught > 2))
    {
        SetVisible(false);
    }
}