/**
 * @file MainFrame.cpp
 * @author Peyton Nagher
 * @author Ben Toaz, Stefan Lemke
 *
 * Create base frame for sudoku GUI
 */

#include "pch.h"
#include "MainFrame.h"
#include "ids.h"
#include "SudokuView.h"
#include "ScoreBoard.h"
#include <wx/event.h>

using namespace std;


/**
* Initialize the MainFrame window.
*/
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Action Sudoku",
           wxDefaultPosition,  wxSize( 960, 720 ));

    auto sizer = new wxBoxSizer( wxVERTICAL );

    mSudokuView = new SudokuView();
    mSudokuView->Initialize(this);

    sizer->Add(mSudokuView, 1, wxEXPAND | wxALL );

    SetSizer( sizer );

    Layout();

    CreateStatusBar();

    auto menuBar = new wxMenuBar();

    auto fileMenu = new wxMenu();
    auto levelMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(levelMenu, "&Level");
    menuBar->Append(helpMenu, "&Help");

    fileMenu->Append(IDM_SOLVE, L"&Solve", L"Solve the sudoku puzzle");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");

    levelMenu->Append(IDM_LEVEL0, "&Level 0", "Switch to level 0");
    levelMenu->Append(IDM_LEVEL1, "&Level 1", "Switch to level 1");
    levelMenu->Append(IDM_LEVEL2, "&Level 2", "Switch to level 2");
    levelMenu->Append(IDM_LEVEL3, "&Level 3", "Switch to level 3");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    SetMenuBar(menuBar);

    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnSolve, this, IDM_SOLVE);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mSudokuView->Stop();
    Destroy();
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * About menu option handlers
 *
 * @param event
 */
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(L"Action Sudoku",
                 L"Action Sudoku",
                 wxOK,
                 this);
}

/**
 * Solve menu option handlers
 *
 * @param event
 */
void MainFrame::OnSolve(wxCommandEvent& event)
{
    mSudokuView->Solve();
}
