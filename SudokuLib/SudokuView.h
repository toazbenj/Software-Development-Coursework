/**
 * @file SudokuView.h
 * @author Peyton Nagher, Ben Toaz, Stefan Lemke
 *
 * User interactions with mainframe GUI
 */

#ifndef PROJECT1_SUDOKULIB_SUDOKUVIEW_H
#define PROJECT1_SUDOKULIB_SUDOKUVIEW_H

#include "Sudoku.h"
#include "ItemSparty.h"

/**
 * Window class to draw the sudoku game
 */
class SudokuView : public wxWindow
{
private:
    /// An object that describes our sudoku
    Sudoku mSudoku;
    /// Sparty object
    std::shared_ptr<ItemSparty> mSpartyInstance;
    /// The timer that allows for animation
    wxTimer mTimer;
    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;
    /// The last stopwatch time
    long mTime = 0;

    void OnPaint(wxPaintEvent& event);
    void OnTimerEvent(wxTimerEvent&);

public:
    SudokuView() = default;
    SudokuView(const Sudoku &) = delete;
    void operator=(const SudokuView &) = delete;

    void Initialize(wxFrame* parent);
    void OnLeftDown(wxMouseEvent &event);
    void OnKeyPress(wxKeyEvent &event);
    void OnLevelZero(wxCommandEvent& event);
    void OnLevelOne(wxCommandEvent& event);
    void OnLevelTwo(wxCommandEvent& event);
    void OnLevelThree(wxCommandEvent& event);

    /**
     * Stop the Timer
     */
    void Stop() { mTimer.Stop(); }
    void Solve();
};

#endif //PROJECT1_SUDOKULIB_SUDOKUVIEW_H
