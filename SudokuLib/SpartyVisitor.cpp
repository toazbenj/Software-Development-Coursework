/**
 * @file SpartyVisitor.cpp
 *
 * @author Peyton Nagher, Ethan Egger
 */

#include "pch.h"
#include "SpartyVisitor.h"
#include "ItemContainer.h"

using namespace std;

/**
 * Visitor function to check if there is a specific item in mItems
 *
 * @param sudoku
 */
void SpartyVisitor::VisitSudoku(Sudoku *sudoku)
{
    auto& items = sudoku->GetItems();
    auto it = std::find(items.begin(), items.end(), mItem);

    if (it != items.end())
    {
        items.erase(it);
        mContainer->AddDigit(mItem);
    }
}

/**
 * Visitor function to either add or remove a digit from an ItemContainer
 *
 * @param digit
 * @param container
 * @param isEaten
 */
void SpartyVisitor::VisitDigit(std::shared_ptr<Item> digit, ItemContainer *container, bool isEaten)
{
    if (isEaten)
    {
        container->AddDigit(digit);
    }
}
