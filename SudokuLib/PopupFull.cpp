/**
 * @file PopupFull.cpp
 *
 * @author Ethan Egger
 */

#include "pch.h"
#include "PopupFull.h"
#include "PopupManager.h"

#include <wx/graphics.h>

/**
 * Draw the "full" popup
 *
 * @param graphics context on which to draw
 */
void PopupFull::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(wxNullGraphicsPen);
    graphics->DrawRectangle(GetXPos() - 90, GetYPos(), 180, 50);

    wxPen linePen(*wxBLACK, 6);
    graphics->SetPen(linePen);
    graphics->StrokeLine(GetXPos() - 90, GetYPos(), GetXPos() + 90, GetYPos());
    graphics->StrokeLine(GetXPos() + 90, GetYPos(), GetXPos() + 90, GetYPos() + 50);
    graphics->StrokeLine(GetXPos() + 90, GetYPos() + 50, GetXPos() - 90, GetYPos() + 50);
    graphics->StrokeLine(GetXPos() - 90, GetYPos() + 50, GetXPos() - 90, GetYPos());

    wxFont bigFont(wxSize(0, 40),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(230, 7, 7));

    double wid, hit;
    graphics->GetTextExtent(L"I'm Full!", &wid, &hit);
    graphics->DrawText(L"I'm Full!", GetXPos() - wid/2, GetYPos() + 5);
}

/**
 * Function to move a popup in the y direction
 *
 * @param elapsed
 */
void PopupFull::Update(double elapsed)
{
    Popup::Update(elapsed);

    auto y = GetYPos() - 500 * elapsed;
    SetYPos(y);
}
