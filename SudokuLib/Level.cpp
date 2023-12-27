/**
 * @file Level.cpp
 * @author Peyton Nagher
 * @author Ethan Egger
 */

#include "pch.h"
#include "Level.h"
#include "DeclarationBackground.h"
#include "DeclarationXRay.h"
#include "DeclarationDigit.h"
#include "DeclarationSparty.h"
#include "DeclarationContainer.h"
#include "DeclarationEnemy.h"

using namespace std;

/**
 * Constructor as well as XML loader for a game level
 * @param levelNode xml attributes
 */
Level::Level(wxXmlNode *levelNode)
{
    levelNode->GetAttribute(L"width").ToInt(&mWidth);
    levelNode->GetAttribute(L"height").ToInt(&mHeight);
    levelNode->GetAttribute(L"tilewidth").ToInt(&mTileWid);
    levelNode->GetAttribute(L"tileheight").ToInt(&mTileHit);

    auto declarationsNode = levelNode->GetChildren();
    auto gameNode = declarationsNode->GetNext();

    wstring solutionString = gameNode->GetChildren()->GetContent().ToStdWstring();
    wstringstream solutionStream(solutionString);
    gameNode->GetAttribute(L"col").ToInt(&mColLowerBound);
    gameNode->GetAttribute(L"row").ToInt(&mRowLowerBound);

    for(wstring digit; solutionStream >> digit; )
    {
        int num = std::stoi(digit);
        mSolution.push_back(num);
    }

    auto child = declarationsNode->GetChildren();

    for(; child; child=child->GetNext())
    {
        XmlDeclaration(child);
    }
}

/**
 * Clears all declarations from the level, effectively removing unique elements
 */
void Level::Clear()
{
    mDeclarations.clear();
}

/**
 * Handle a node of type declaration.
 *
 * @param node XML node
 */
void Level::XmlDeclaration(wxXmlNode *node)
{
    shared_ptr<Declaration> declaration;
    const auto& name = node->GetName();
    auto id = node->GetAttribute(L"id");

    if(name == L"background")
    {
        declaration = make_shared<DeclarationBackground>(node);
    }
    else if(name == L"xray")
    {
        declaration = make_shared<DeclarationXRay>(node);
    }
    else if(name == L"digit" || name == L"given")
    {
        declaration = make_shared<DeclarationDigit>(node);
    }
    else if(name == L"sparty")
    {
        declaration = make_shared<DeclarationSparty>(node);
    }
    else if(name == L"container")
    {
        declaration = make_shared<DeclarationContainer>(node);
    }
    else if(name == L"enemy")
    {
        declaration = make_shared<DeclarationEnemy>(node);
    }

    mDeclarations[id] = (declaration);
}

/**
 * @return map of declaration shared pointers
 */
unordered_map<wxString, shared_ptr<Declaration>> Level::GetDeclarations()
{
    return mDeclarations;
}

/**
 * @return vector representing the level's solution
 */
vector<int> Level::GetSolution()
{
    return mSolution;
}