/**
 * @file MainFrame.h
 * @author Peyton Nagher, Stefan Lemke
 *
 * Create base frame for sudoku GUI
 */

#ifndef PROJECT1_SUDOKULIB_MAINFRAME_H
#define PROJECT1_SUDOKULIB_MAINFRAME_H

#include "SudokuView.h"
/// View and event manager
class MainFrame : public wxFrame
{
private:
    /// pointer to a SudokuView object
    SudokuView *mSudokuView = nullptr;

public:
    MainFrame() = default;
    MainFrame(const Sudoku &) = delete;
    void operator=(const MainFrame &) = delete;
    void Initialize();
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent &event);
    void OnClose(wxCloseEvent &event);
    void OnSolve(wxCommandEvent &event);
};

#endif //PROJECT1_SUDOKULIB_MAINFRAME_H
