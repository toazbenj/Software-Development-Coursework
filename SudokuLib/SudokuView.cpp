/**
 * @file SudokuView.cpp
 * @author Peyton Nagher, Ben Toaz
 *
 * User interactions with mainframe GUI
 */

#include "pch.h"
#include <memory>
#include "SudokuView.h"
#include <wx/dcbuffer.h>
#include <wx/graphics.h>
#include <wx/string.h>
#include <string>
#include "ids.h"
#include "Popup.h"
#include "ItemSparty.h"
#include "DeclarationSparty.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
 * Initialize the Sudoku view class.
 *
 * @param mainFrame The parent window for this class
 */
void SudokuView::Initialize(wxFrame* mainFrame)
{
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    Create(mainFrame, wxID_ANY,
        wxDefaultPosition, wxDefaultSize,
        wxFULL_REPAINT_ON_RESIZE);

    SetBackgroundColour(*wxBLACK);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevelZero, this, IDM_LEVEL0);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevelOne, this, IDM_LEVEL1);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevelTwo, this, IDM_LEVEL2);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &SudokuView::OnLevelThree, this, IDM_LEVEL3);
    Bind(wxEVT_KEY_DOWN, &SudokuView::OnKeyPress, this);
    Bind(wxEVT_PAINT, &SudokuView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &SudokuView::OnLeftDown, this);
    Bind(wxEVT_TIMER, &SudokuView::OnTimerEvent, this);
    mStopWatch.Start();
}

/**
 * Paint event, draws the window.
 *
 * @param event Paint event object
 */
void SudokuView::OnPaint(wxPaintEvent& event)
{
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;
    mSudoku.Update(elapsed);
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    wxRect rect = GetRect();
    mSudoku.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}

/**
 * Handle the left mouse button down event
 *
 * @param event The mouse click event
 */
void SudokuView::OnLeftDown(wxMouseEvent &event)
{
    mSudoku.OnLeftDown(event.GetX(), event.GetY());
}

/**
 * Handle a key press event (space, B, num)
 *
 * @param event Key press in question
 */
void SudokuView::OnKeyPress(wxKeyEvent &event)
{
    wxChar keyChar = event.GetUnicodeKey();
    int targetNum;
    wstringstream keyStream;
    keyStream << keyChar;

    if ( keyChar == ' ')
    {
        mSudoku.OnSpaceDown();
    }
    else if ( keyChar == 'B')
    {
        mSudoku.OnBDown();
    }
    else if (keyStream >> targetNum)
    {
        mSudoku.OnNumKeyDown(targetNum);
    }
}

/**
 * Handle the level zero event
 *
 * @param event
 */
void SudokuView::OnLevelZero(wxCommandEvent& event)
{
    const wxString filename = L"Levels/level0.xml";
    mSudoku.Load(filename, 0);
    mSudoku.SetNewLevel(true);
}

/**
 * Handle the level one event
 *
 * @param event
 */
void SudokuView::OnLevelOne(wxCommandEvent& event)
{
    const wxString filename = "Levels/level1.xml";
    mSudoku.Load(filename, 1);
    mSudoku.SetNewLevel(true);
}

/**
 * Handle the level two event
 *
 * @param event
 */
void SudokuView::OnLevelTwo(wxCommandEvent& event)
{
    const wxString filename = L"Levels/level2.xml";
    mSudoku.Load(filename, 2);
    mSudoku.SetNewLevel(true);
}

/**
 * Handle the level three event
 *
 * @param event
 */
void SudokuView::OnLevelThree(wxCommandEvent& event)
{
    const wxString filename = L"Levels/level3.xml";
    mSudoku.Load(filename, 3);
    mSudoku.SetNewLevel(true);
}

/**
 * Handler for timer events to update the screen
 *
 * @param event
 */
void SudokuView::OnTimerEvent(wxTimerEvent &event)
{
    Refresh();
}

/**
 * Load solved game xml in sudoku member
 */
void SudokuView::Solve()
{
    mSudoku.Solve();
}
