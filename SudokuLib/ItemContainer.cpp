/**
 * @file ItemContainer.cpp
 * @author Peyton Nagher
 */

#include "pch.h"
#include "ItemContainer.h"
#include "DeclarationContainer.h"
#include "Sudoku.h"
#include "Visitor.h"
#include <random>

using namespace std;

/**
 * Load container and all its contents
 * @param node XML node representing container object
 */
void ItemContainer::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

    auto child = node->GetChildren();
    for(; child; child = child->GetNext())
    {
        auto id = child->GetAttribute(L"id");
        auto sudoku = GetSudoku();
        auto dec = sudoku->GetLevel()->GetDeclaration(id);

        auto item = dec->Create(sudoku, child);
        item->XmlLoad(child);
        mItems.push_back(item);
    }
}

/**
 * Getter for width
 * @return return declaration width
 */
double ItemContainer::GetWidth() const
{
    return mDeclaration->GetWidth();
}

/**
 * Getter for height
 * @return return declaration height
 */
double ItemContainer::GetHeight() const
{
    return mDeclaration->GetHeight();
}

/**
 * Draw container
 * @param graphics Graphics context to draw on
 */
void ItemContainer::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mDeclaration->Draw(graphics, GetRow(), GetCol());
    for(auto item : mItems)
    {
        item->Draw(graphics);
    }
    mDeclaration->DrawFront(graphics, GetRow(), GetCol());
}

/**
 *
 * @param visitor
 */
void ItemContainer::Accept(Visitor *visitor)
{
    visitor->VisitContainer(this);
}

/**
 *
 * @param digit
 */
void ItemContainer::AddDigit(std::shared_ptr<Item> digit)
{
    mItems.push_back(std::shared_ptr<Item>(digit));
}

/**
 * Remove all digits from container and place them in Sudoku class
 */
void ItemContainer::ReleaseDigits()
{
    while(!mItems.empty())
    {
        auto digit = mItems.back();
        mItems.pop_back();

        auto minCol = GetCol() - 0.15 * mDeclaration->GetWidth() / GetLevelTileWidth();
        auto maxCol = GetCol() + 1.15 * mDeclaration->GetWidth() / GetLevelTileWidth();
        uniform_real_distribution<> colDistribution(minCol, maxCol);

        auto minRow = GetRow() - 1.5 * mDeclaration->GetHeight() / GetLevelTileHeight();
        auto maxRow = GetRow() - 0.75 * mDeclaration->GetHeight() / GetLevelTileHeight();
        uniform_real_distribution<> rowDistribution(minRow, maxRow);

        auto col = colDistribution(GetSudoku()->GetRandom());
        auto row = rowDistribution(GetSudoku()->GetRandom());

        digit->SetLocation(col, row);
        GetSudoku()->Add(digit);
    }
}
