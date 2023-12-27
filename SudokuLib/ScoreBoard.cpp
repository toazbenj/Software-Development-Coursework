/**
 * @file ScoreBoard.cpp
 *
 * @author Abhi Rao
 *
 * Functions that support ScoreBoard
 */

#include "pch.h"
#include "ScoreBoard.h"
#include "Sudoku.h"
#include <wx/graphics.h>

using namespace std;

/// Size of the scoreboard text in virtual pixels
const int ScoreboardTextSize = 64;

/**
 * Update the seconds elapsed
 * @param elapsed
 */
void ScoreBoard::Update(double elapsed)
{
    mSecondsElapsed += elapsed;
}

/**
 * Calls DrawTime
 *
 * @param graphics
 */
void ScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    DrawTime(graphics);
}

/**
 * Resets the seconds elapsed to zero
 */
void ScoreBoard::Reset()
{
    mSecondsElapsed = 0;
}

/**
 * Returns time elapsed
 *
 * @return seconds elapsed
 */
double ScoreBoard::GetElapsedSeconds() const {
    return mSecondsElapsed;
}

/**
 * Handles formatting the timer that will be displayed
 *
 * @param graphics
 */
void ScoreBoard::DrawTime(std::shared_ptr<wxGraphicsContext> graphics)
{
    int min = (int)mSecondsElapsed / 60;
    int sec = (int)mSecondsElapsed % 60;
    wxString timeStr = wxString::Format(wxT("%01d:%02d"), min, sec);
    wxFont font(ScoreboardTextSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, *wxWHITE);
    graphics->DrawText(timeStr, 10, 10);
}
