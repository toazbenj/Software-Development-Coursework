/**
 * @file ScoreBoardTest.cpp
 * @author Abhi Rao
 */

#include <pch.h>
#include <SudokuView.h>
#include <ScoreBoard.h>
#include <wx/frame.h>
#include "gtest/gtest.h"
#include <thread>
#include <chrono>



class TestableScoreBoard : public ScoreBoard {
public:

};

class ScoreBoardTest : public ::testing::Test {
protected:
    SudokuView sudokuView;
    TestableScoreBoard scoreBoard;
};

TEST_F(ScoreBoardTest, TimeElapsedTest) {
    auto initialTime = scoreBoard.GetElapsedSeconds();
    scoreBoard.Update(2.0);
    auto afterUpdate = scoreBoard.GetElapsedSeconds();

    ASSERT_NE(initialTime, afterUpdate);
    ASSERT_EQ(afterUpdate - initialTime, 2.0);
}

