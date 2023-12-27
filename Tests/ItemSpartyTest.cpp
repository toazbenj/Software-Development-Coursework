/**
 * @file SpartyTest.cpp
 * @author Peyton Nagher
 */
#include <pch.h>
#include <Level.h>
#include <ItemSparty.h>
#include <DeclarationSparty.h>
#include <Sudoku.h>
#include <gtest/gtest.h>

TEST(ItemSpartyTest, Construct)
{
    wxXmlNode* node = new wxXmlNode(wxXML_ELEMENT_NODE, "sparty_test");
    Sudoku sudoku;
    DeclarationSparty declaration(node);
    ItemSparty sparty(&sudoku, &declaration);

    ASSERT_EQ(sparty.GetDeclaration(), &declaration);

    ASSERT_FALSE(sparty.GetEating());

    ASSERT_FALSE(sparty.GetRegurgitating());

    ASSERT_FALSE(sparty.GetHeadbutting());

    delete node;
}


TEST(ItemSpartyTest, XmlLoad)
{
    wxXmlDocument xmlDoc;
    wxString file = L"Levels/level0.xml";
    xmlDoc.Load(file);

    auto node = xmlDoc.GetRoot()->GetChildren()->GetChildren();
    while(node->GetName() != L"sparty")
    {
        node = node->GetNext();
    }

    Sudoku sudoku;
    DeclarationSparty declaration(node);
    ItemSparty sparty(&sudoku, &declaration);

    sparty.XmlLoad(node);

    ASSERT_EQ(sparty.GetRow(), 10.8333);
    ASSERT_EQ(sparty.GetCol(), 1.4167);

    delete node;
}
