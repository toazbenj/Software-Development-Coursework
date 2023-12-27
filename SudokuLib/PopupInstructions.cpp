/**
 * @file PopupInstructions.cpp
 * @author Ethan Egger
 */

#include "pch.h"
#include "PopupInstructions.h"
#include "PopupManager.h"
#include "Sudoku.h"

#include <sstream>
#include <wx/graphics.h>

/**
 * Draw the popup
 *
 * @param graphics Context on which to draw
 */
void PopupInstructions::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (!IsVisible())
    {
        return;
    }

    wxPen linePen(*wxBLACK, 3);
    graphics->SetPen(linePen);
    graphics->StrokeLine(GetXPos()-350, GetYPos() - 190, GetXPos()+350, GetYPos() - 190);
    graphics->StrokeLine(GetXPos()-350+700, GetYPos() - 190, GetXPos()-350+700, GetYPos() - 190+319);
    graphics->StrokeLine(GetXPos()-350+700, GetYPos() - 190+319, GetXPos()-350, GetYPos() - 190+319);
    graphics->StrokeLine(GetXPos()-350, GetYPos() - 190+319, GetXPos()-350, GetYPos() - 190);

    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(wxNullGraphicsPen);
    graphics->DrawRectangle(GetXPos()-350, GetYPos() - 190, 700, 319);

    wxFont bigFont(wxSize(0, 100),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(10, 171, 29));

    double wid, hit;

    std::wstringstream text;
    int levelNumber = GetManager()->GetSudoku()->GetLevelNum();
    text << "Level " << levelNumber << " Begin";
    graphics->GetTextExtent(text.str(), &wid, &hit);
    graphics->DrawText(text.str(), GetXPos() - wid/2, GetYPos() - 125 - hit/2);

    wxFont instructionFont(wxSize(0, 50),
                           wxFONTFAMILY_SWISS,
                           wxFONTSTYLE_NORMAL,
                           wxFONTWEIGHT_BOLD);
    graphics->SetFont(instructionFont, wxColour(0, 0, 0));

    graphics->GetTextExtent(L"space: Eat", &wid, &hit);
    graphics->DrawText(L"space: Eat", GetXPos() - wid/2, GetYPos() - 30 - hit/2);

    graphics->GetTextExtent(L"0-8: Regurgitate", &wid, &hit);
    graphics->DrawText(L"0-8: Regurgitate", GetXPos() - wid/2, GetYPos() + 30 - hit/2);

    graphics->GetTextExtent(L"B: Headbutt", &wid, &hit);
    graphics->DrawText(L"B: Headbutt", GetXPos() - wid/2, GetYPos() + 90 - hit/2);
}

/**
 * Function to spawn and de-spawn the instruction popup
 *
 * @param elapsed
 */
void PopupInstructions::Update(double elapsed)
{
    Popup::Update(elapsed);

    if (IsVisible() && GetManager()->GetSudoku()->IsFrozen() && GetElapsed() > 3)
    {
        SetVisible(false);
        GetManager()->GetSudoku()->Unfreeze();
    }
}
