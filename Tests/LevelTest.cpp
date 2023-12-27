/**
 * @file LevelTest.cpp
 * @author ethan
 */

#include <pch.h>
#include <Level.h>

#include "gtest/gtest.h"

TEST(LevelTest, Construct)
{
    wxXmlDocument xmlDoc;
    wxString file = L"Levels/level0.xml";
    xmlDoc.Load(file);

    auto root = xmlDoc.GetRoot();

    Level level(root);
    auto decs = level.GetDeclarations();
    ASSERT_EQ(decs.size(), 21);

    auto soln = level.GetSolution();
    ASSERT_EQ(soln.size(), 81);
}