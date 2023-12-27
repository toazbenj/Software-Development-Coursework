/**
 * @file ScoreBoard.h
 *
 * @author Abhi Rao
 *
 * Base class for ScoreBoard
 */

#ifndef PROJECT1_SUDOKULIB_SCOREBOARD_H
#define PROJECT1_SUDOKULIB_SCOREBOARD_H

#include <wx/wx.h>
#include <wx/timer.h>

/// timer class
class ScoreBoard : public wxPanel {
private:
    /// elapsed time value
    double mSecondsElapsed = 0;
public:
    void Update(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void Reset();
    void DrawTime(std::shared_ptr<wxGraphicsContext> graphics);
    double GetElapsedSeconds() const;
};

#endif //PROJECT1_SUDOKULIB_SCOREBOARD_H
