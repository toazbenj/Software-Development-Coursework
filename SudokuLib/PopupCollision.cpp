/**
 * @file PopupCollision.cpp
 *
 * @author Ethan Egger
 */

#include "pch.h"
#include "PopupCollision.h"
#include "PopupManager.h"

#include <wx/graphics.h>

/**
 * Draw the "full" popup
 *
 * @param graphics context on which to draw
 */
void PopupCollision::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(wxNullGraphicsPen);
    graphics->DrawRectangle(GetXPos() - 250, GetYPos(), 500, 50);

    wxPen linePen(*wxBLACK, 6);
    graphics->SetPen(linePen);
    graphics->StrokeLine(GetXPos() - 250, GetYPos(), GetXPos() + 250, GetYPos());
    graphics->StrokeLine(GetXPos() + 250, GetYPos(), GetXPos() + 250, GetYPos() + 50);
    graphics->StrokeLine(GetXPos() + 250, GetYPos() + 50, GetXPos() - 250, GetYPos() + 50);
    graphics->StrokeLine(GetXPos() - 250, GetYPos() + 50, GetXPos() - 250, GetYPos());

    wxFont bigFont(wxSize(0, 35),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(230, 7, 7));

    double wid, hit;
    graphics->GetTextExtent(L"Something is already there!", &wid, &hit);
    graphics->DrawText(L"Something is already there!", GetXPos() - wid/2, GetYPos() + 5);
}

/**
 * Function to move a popup in the y direction
 *
 * @param elapsed
 */
void PopupCollision::Update(double elapsed)
{
    Popup::Update(elapsed);

    auto y = GetYPos() - 500 * elapsed;
    SetYPos(y);
}
