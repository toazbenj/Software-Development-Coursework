/**
 * @file Popup.cpp
 * @author Stefan Lemke
 *
 * Popup drawing class
 */

#include "pch.h"
#include "Popup.h"
#include "DeclarationBackground.h"
#include "PopupManager.h"
#include <wx/graphics.h>
#include <sstream>

using namespace std;

/**
 * Constructor
 *
 * @param manager Manager object that owns this popup
 * @param x X Position of popup
 * @param y Y Position of popup
 * @param w Width of popup
 * @param h Height of popup
 */
Popup::Popup(PopupManager *manager, double x, double y, double w, double h)
{
    mManager = manager;
    mXPos = x;
    mYPos = y;
    mWidth = w;
    mHeight = h;
    mSecondsElapsed = 0;
}

/**
 * Updates the elapsed time for the popup
 *
 * @param elapsed time offset
 */
void Popup::Update(double elapsed)
{
    mSecondsElapsed += elapsed;
}

/**
 * Makes popup visible
 *
 * @param visible bool flag
 */
void Popup::SetVisible(bool visible)
{
    mVisible = visible;
}

/**
 * Function to make the instructions popup
 *
 * @param graphics context for drawing
 * @param pixelWidth size
 * @param pixelHeight size
 * @param levelNumber current level
 */
void Popup::Instructions(std::shared_ptr<wxGraphicsContext> graphics, int pixelWidth, int pixelHeight, int levelNumber)
{
    wxPen linePen(*wxBLACK, 3);
    graphics->SetPen(linePen);
    graphics->StrokeLine(pixelWidth/2-350, pixelHeight/2 - 190, pixelWidth/2-350+700, pixelHeight/2 - 190);
    graphics->StrokeLine(pixelWidth/2-350+700, pixelHeight/2 - 190, pixelWidth/2-350+700, pixelHeight/2 - 190+319);
    graphics->StrokeLine(pixelWidth/2-350+700, pixelHeight/2 - 190+319, pixelWidth/2-350, pixelHeight/2 - 190+319);
    graphics->StrokeLine(pixelWidth/2-350, pixelHeight/2 - 190+319, pixelWidth/2-350, pixelHeight/2 - 190);

    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(wxNullGraphicsPen);
    graphics->DrawRectangle(pixelWidth/2-350, pixelHeight/2 - 190, 700, 319);

    wxFont bigFont(wxSize(0, 100),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(10, 171, 29));

    double wid, hit;

    std::wstringstream text;
    text << "Level " << std::to_string(levelNumber) << " Begin";
    graphics->GetTextExtent(text.str(), &wid, &hit);
    graphics->DrawText(text.str(), pixelWidth/2 - wid/2, pixelHeight/2 - 125 - hit/2);

    wxFont instructionFont(wxSize(0, 50),
                           wxFONTFAMILY_SWISS,
                           wxFONTSTYLE_NORMAL,
                           wxFONTWEIGHT_BOLD);
    graphics->SetFont(instructionFont, wxColour(0, 0, 0));

    graphics->GetTextExtent(L"space: Eat", &wid, &hit);
    graphics->DrawText(L"space: Eat", pixelWidth/2 - wid/2, pixelHeight/2 - 30 - hit/2);

    graphics->GetTextExtent(L"0-8: Regurgitate", &wid, &hit);
    graphics->DrawText(L"0-8: Regurgitate", pixelWidth/2 - wid/2, pixelHeight/2 + 30 - hit/2);

    graphics->GetTextExtent(L"B: Headbutt", &wid, &hit);
    graphics->DrawText(L"B: Headbutt", pixelWidth/2 - wid/2, pixelHeight/2 + 90 - hit/2);
}

/**
 * Draw sparty full popup
 *
 * @param graphics context for drawing
 * @param pixelWidth size
 * @param pixelHeight size
 */
void Popup::Full(std::shared_ptr<wxGraphicsContext> graphics, double pixelWidth, double pixelHeight)
{
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(wxNullGraphicsPen);
    graphics->DrawRectangle(pixelWidth/2 - 90, pixelHeight/2 + mYPos, 180, 50);

    wxPen linePen(*wxBLACK, 6);
    graphics->SetPen(linePen);
    graphics->StrokeLine(pixelWidth/2 - 90, pixelHeight/2 + mYPos, pixelWidth/2 + 90, pixelHeight/2 + mYPos);
    graphics->StrokeLine(pixelWidth/2 + 90, pixelHeight/2 + mYPos, pixelWidth/2 + 90, pixelHeight/2 + 50 + mYPos);
    graphics->StrokeLine(pixelWidth/2 + 90, pixelHeight/2 + 50 + mYPos, pixelWidth/2 - 90, pixelHeight/2 + 50 + mYPos);
    graphics->StrokeLine(pixelWidth/2 - 90, pixelHeight/2 + 50 + mYPos, pixelWidth/2 - 90, pixelHeight/2 + mYPos);

    wxFont bigFont(wxSize(0, 40),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(230, 7, 7));

    double wid, hit;
    graphics->GetTextExtent(L"I'm Full!", &wid, &hit);
    graphics->DrawText(L"I'm Full!", pixelWidth/2 - wid/2, pixelHeight/2 + 5 + mYPos);
}

/**
 * Function to make the popup that appears when X-Ray is full
 *
 * @param graphics context for drawing
 * @param pixelWidth size
 * @param pixelHeight size
 */
void Popup::Collision(std::shared_ptr<wxGraphicsContext> graphics, double pixelWidth, double pixelHeight)
{
    wxBrush rectBrush(*wxWHITE);
    graphics->SetBrush(rectBrush);
    graphics->SetPen(wxNullGraphicsPen);
    graphics->DrawRectangle(pixelWidth/2 - 250, pixelHeight/2 + mYPos, 500, 50);

    wxPen linePen(*wxBLACK, 6);
    graphics->SetPen(linePen);
    graphics->StrokeLine(pixelWidth/2 - 250, pixelHeight/2 + mYPos, pixelWidth/2 + 250, pixelHeight/2 + mYPos);
    graphics->StrokeLine(pixelWidth/2 + 250, pixelHeight/2 + mYPos, pixelWidth/2 + 250, pixelHeight/2 + 50 + mYPos);
    graphics->StrokeLine(pixelWidth/2 + 250, pixelHeight/2 + 50 + mYPos, pixelWidth/2 - 250, pixelHeight/2 + 50 + mYPos);
    graphics->StrokeLine(pixelWidth/2 - 250, pixelHeight/2 + 50 + mYPos, pixelWidth/2 - 250, pixelHeight/2 + mYPos);

    wxFont bigFont(wxSize(0, 35),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(230, 7, 7));

    double wid, hit;
    graphics->GetTextExtent(L"Something is already there!", &wid, &hit);
    graphics->DrawText(L"Something is already there!", pixelWidth/2 - wid/2, pixelHeight/2 + 5 + mYPos);
}

/**
 * Function to make win/loss popup
 *
 * @param graphics context for drawing
 * @param pixelWidth size
 * @param pixelHeight size
 * @param win flag for solution status
 */
void Popup::WinLoss(std::shared_ptr<wxGraphicsContext> graphics, double pixelWidth, double pixelHeight, bool win)
{
    wxFont bigFont(wxSize(0, 100),
                   wxFONTFAMILY_SWISS,
                   wxFONTSTYLE_NORMAL,
                   wxFONTWEIGHT_BOLD);
    graphics->SetFont(bigFont, wxColour(10, 171, 29));
    double wid, hit;
    if (win)
    {
        graphics->GetTextExtent(L"Level Complete!", &wid, &hit);
        graphics->DrawText(L"Level Complete!", pixelWidth/2 - wid/2, pixelHeight/2 - hit/2);
    }
    else
    {
        graphics->GetTextExtent(L"Incorrect!", &wid, &hit);
        graphics->DrawText(L"Incorrect!", pixelWidth/2 - wid/2, pixelHeight/2 - hit/2);
    }
}
/**
 * Function to make caught popup
 */
void Popup::Caught() {}
