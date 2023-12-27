/**
 * @file ItemXRay.cpp
 * @author Peyton Nagher
 * @author Ben Toaz
 */

#include "pch.h"
#include "ItemXRay.h"
#include "Item.h"
#include "DeclarationXRay.h"
#include "Sudoku.h"
#include "Visitor.h"

#include <random>

using namespace std;

/// Image file name
const wstring filename = L"images/xray.png";


/**
 * Constructor for an XRay item based on a respective declaration
 *
 * @param PSudoku
 * @param declaration
 */
ItemXRay::ItemXRay(Sudoku *PSudoku, DeclarationXRay *declaration): Item(PSudoku)
{
    mDeclaration = declaration;
}

/**
 * Adds a digit to the XRay stomach
 *
 * @param digit
 */
void ItemXRay::AddDigit(shared_ptr<Item> digit)
{
    auto minCol = GetCol() + 0.1 * mDeclaration->GetWidth() / GetLevelTileWidth();
    auto maxCol = GetCol() + 0.9 * mDeclaration->GetWidth() / GetLevelTileWidth() - digit->GetWidth() / GetLevelTileWidth();
    uniform_real_distribution<> colDistribution(minCol, maxCol);

    auto minRow = GetRow() - 0.9 * mDeclaration->GetHeight() / GetLevelTileHeight() + digit->GetHeight() / GetLevelTileHeight();
    auto maxRow = GetRow() - 0.1 * mDeclaration->GetHeight() / GetLevelTileHeight();
    uniform_real_distribution<> rowDistribution(minRow, maxRow);

    auto col = colDistribution(GetSudoku()->GetRandom());
    auto row = rowDistribution(GetSudoku()->GetRandom());

    digit->SetLocation(col, row);

    mItems.push_back(digit);
}

/**
 * Removes a digit from the XRay stomach and places it where appropriate
 *
 * @param digit
 * @return
 */
shared_ptr<Item> ItemXRay::PopDigit(ItemDigitMovable* digit)
{
    for (auto itr = mItems.begin(); itr != mItems.end(); ++itr)
    {
        if (itr->get() == digit)
        {
            auto digit = *itr;
            mItems.erase(itr);
            return digit;
        }
    }
    return nullptr;
}

/**
 * Remove all digits from container and place them in Sudoku class
 */
void ItemXRay::ReleaseDigits()
{
    while(!mItems.empty())
    {
        auto digit = mItems.back();
        mItems.pop_back();

        auto minCol = GetCol() - 0.15 * mDeclaration->GetWidth() / GetLevelTileWidth();
        auto maxCol = GetCol() + 1.15 * mDeclaration->GetWidth() / GetLevelTileWidth();
        uniform_real_distribution<> colDistribution(minCol, maxCol);

        auto minRow = GetRow() - 1.5 * mDeclaration->GetHeight() / GetLevelTileHeight();
        auto maxRow = GetRow() - mDeclaration->GetHeight() / GetLevelTileHeight();
        uniform_real_distribution<> rowDistribution(minRow, maxRow);

        auto col = colDistribution(GetSudoku()->GetRandom());
        auto row = rowDistribution(GetSudoku()->GetRandom());

        digit->SetLocation(col, row);
        GetSudoku()->Add(digit);
    }
}

/**
 * Draw X-Ray of stomach
 *
 * @param graphics Graphics context to draw on
 */
void ItemXRay::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mDeclaration->Draw(graphics, GetRow(), GetCol());

    for (auto digit : mItems)
    {
        graphics->PushState();
        graphics->Translate(digit->GetCol() * GetLevelTileWidth(), digit->GetRow() * GetLevelTileHeight());
        graphics->Scale(0.65, 0.65);
        graphics->Translate(-digit->GetCol() * GetLevelTileWidth(), -digit->GetRow() * GetLevelTileHeight());
        digit->Draw(graphics);
        graphics->PopState();
    }
}

/**
 * Accepts a visitor for the XRay
 *
 * @param visitor
 */
void ItemXRay::Accept(Visitor *visitor)
{
    visitor->VisitXRay(this);
}

/**
 * Calls the Accept function on each item within mItems
 *
 * @param visitor
 */
void ItemXRay::ContentsAccept(Visitor *visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}