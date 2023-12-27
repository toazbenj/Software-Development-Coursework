/**
 * @file ItemBackground.cpp
 *
 * @author Ethan Egger
 */

#include "pch.h"
#include "ItemBackground.h"
#include "Item.h"
#include "DeclarationBackground.h"

using namespace std;


/**
 *
 * @param sudoku
 * @param declaration
 */
ItemBackground::ItemBackground(Sudoku *sudoku, DeclarationBackground *declaration) : Item(sudoku)
{
    mDeclaration = declaration;
}

/**
 *
 * Draw X-Ray of stomach
 * @param graphics Graphics context to draw on
 */
void ItemBackground::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mDeclaration->Draw(graphics, GetRow(), GetCol());
}
