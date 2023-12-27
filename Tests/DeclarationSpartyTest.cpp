/**
 * @file DeclarationSpartyTest.cpp
 * @author ethan
 */

#include <pch.h>
#include <DeclarationSparty.h>
#include <Sudoku.h>

#include "gtest/gtest.h"

TEST(DeclarationSpartyTest, Construct)
{
    wxXmlDocument xmlDoc;
    wxString file = L"Levels/level0.xml";
    xmlDoc.Load(file);

    auto node = xmlDoc.GetRoot()->GetChildren()->GetChildren();
    while(node->GetName() != L"sparty")
    {
        node = node->GetNext();
    }

    DeclarationSparty decSparty(node);
    ASSERT_NEAR(decSparty.GetHeadPivotAngle(), 0.8, 0.00001);
}

TEST(DeclarationSpartyTest, Create)
{
    wxXmlDocument xmlDoc;
    wxString file = L"Levels/level0.xml";
    xmlDoc.Load(file);

    auto root = xmlDoc.GetRoot();
    auto decs = root->GetChildren();
    auto node = decs->GetChildren();
    while(node->GetName() != L"sparty")
    {
        node = node->GetNext();
    }

    DeclarationSparty decSparty(node);

    auto items = decs->GetNext()->GetNext();
    node = items->GetChildren();
    while(node->GetName() != L"sparty")
    {
        node = node->GetNext();
    }

    Sudoku sudoku;

    auto itemSparty = decSparty.Create(&sudoku, node);

    ASSERT_NE(itemSparty, nullptr);
    ASSERT_EQ(itemSparty, sudoku.GetSparty());
    itemSparty->XmlLoad(node);
    ASSERT_NEAR(itemSparty->GetCol(), 1.4167, 0.00001);
}