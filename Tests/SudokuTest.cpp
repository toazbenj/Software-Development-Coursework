/**
 * @file SudokuTest.cpp
 * @author Ben Toaz
 *
 * Make sure that the app is functioning properly
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Sudoku.h>
#include <SudokuView.h>
#include <ScoreBoard.h>
#include <Declaration.h>
#include <SudokuVisitor.h>

using namespace std;

TEST(SudokuTest, Construct)
{
    Sudoku sudoku;
}

TEST(SudokuTest, Load)
{
    Sudoku sudoku;

    // Check for level 0
    sudoku.Load(L"Levels/level0.xml", 0);
    std::vector<std::shared_ptr<Item>> items = sudoku.GetItems();

    ASSERT_EQ(items.size(), 84);

    // Check for level 1
    sudoku.Load(L"Levels/level1.xml", 1);
    items = sudoku.GetItems();

    ASSERT_EQ(items.size(), 84);

    // Check for level 2
    sudoku.Load(L"Levels/level2.xml", 2);
    items = sudoku.GetItems();

    ASSERT_EQ(items.size(), 71);
}

TEST(SudokuTest, Miscellaneous)
{
    Sudoku sudoku;
    sudoku.Load(L"Levels/level1.xml", 1);

//     check if member variable were initialized
    ASSERT_NE(sudoku.GetSparty(),nullptr);
    ASSERT_NE(sudoku.GetLevel(),nullptr);
    ASSERT_NE(sudoku.GetScoreBoard(),nullptr);
    ASSERT_NE(sudoku.GetItems().size(),0);
//    ASSERT_EQ(sudoku.GetRowBounds(),std::tuple<int>((4,12)));
//    ASSERT_EQ(sudoku.GetColBounds(),std::tuple<int>((3,11)));
}


TEST(SudokuTest, Visitor)
{
    //level 0
    Sudoku sudoku;
    sudoku.Load(L"Levels/level0.xml", 0);

    SudokuVisitor visitor(sudoku.GetLevel()->GetBoardBounds());
    sudoku.Accept(&visitor);

    //all the givens on the board
    std::vector<int> answer = {3,2,4,7,6,0,1,5,
                                7,5,6,2,0,1,4,8,
                                0,8,4,3,5,7,6,2,
                                6,4,8,0,7,3,5,
                                2,7,5,3,1,8,6,4,
                                3,0,6,5,4,8,2,7,
                                5,1,2,3,8,
                                8,1,2,7,6,3,4,0,
                                4,0,3,5,8,2,1,7,6};
    std::vector<int> currentAnswer = visitor.GetAnswer();
    //visitor goes through all items, collects values of just the digits on the board
    ASSERT_EQ(currentAnswer, answer);
    // have to rework this one, ints vs wstrings
    ASSERT_NE(currentAnswer, sudoku.GetLevel()->GetSolution());

    //level 1
    sudoku.Load(L"Levels/level1.xml", 1);

    SudokuVisitor visitor1(sudoku.GetLevel()->GetBoardBounds());
    sudoku.Accept(&visitor1);

    //all the givens on the board
    answer = {7,4,5,2,
                6,3,
                3,2,1,
                3,2,5,8,
                8,0,
                5,6,3,1,
                2,3,4,
                8,7,
                6,7,0,5};
    currentAnswer = visitor1.GetAnswer();
    //visitor goes through all items, collects values of just the digits on the board
    ASSERT_EQ(currentAnswer, answer);
    // have to rework this one, ints vs wstrings
    ASSERT_NE(currentAnswer, sudoku.GetLevel()->GetSolution());

    //level 2
    sudoku.Load(L"Levels/level2.xml", 2);

    SudokuVisitor visitor2(sudoku.GetLevel()->GetBoardBounds());
    sudoku.Accept(&visitor2);

    //all the givens on the board
    answer = {7,3,4,1,
                3,8,5,7,
                8,1,4,
                3,4,7,6,
                4,5,2,1,
                6,8,2,3,
                6,8,0,
                3,5,2,7,
                8,2,1,4};
    currentAnswer = visitor2.GetAnswer();
    //visitor goes through all items, collects values of just the digits on the board
    ASSERT_EQ(currentAnswer, answer);
    // have to rework this one, ints vs wstrings

    ASSERT_NE(currentAnswer, sudoku.GetLevel()->GetSolution());

    //level 3
    sudoku.Load(L"Levels/level3.xml", 3);

    SudokuVisitor visitor3(sudoku.GetLevel()->GetBoardBounds());
    sudoku.Accept(&visitor3);

    //all the givens on the board
    answer = {0, 8, 1, 6, 8, 1, 6, 8, 7};
    currentAnswer = visitor3.GetAnswer();
    //visitor goes through all items, collects values of just the digits on the board
    ASSERT_EQ(currentAnswer, answer);
    // have to rework this one, ints vs wstrings
    ASSERT_NE(currentAnswer, sudoku.GetLevel()->GetSolution());
}