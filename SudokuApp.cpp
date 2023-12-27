/**
 * @file SudokuApp.cpp
 *
 * @author Peyton Nagher, Ben Toaz, Stefan Lemke, Ethan Egger, Abhi Rhao
 */

#include "pch.h"
#include <MainFrame.h>
#include "SudokuApp.h"

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#endif

/**
 * Launch ActionSudoku
 *
 * @return success flag
 */
bool SudokuApp::OnInit()
{
    #ifdef WIN32
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    if (!wxApp::OnInit())
        return false;

    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}