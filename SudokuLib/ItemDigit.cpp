/**
 * @file ItemDigit.cpp
 * @author Peyton Nagher, Abhi Rao
 *
 */

#include "pch.h"
#include "ItemDigit.h"
#include "DeclarationDigit.h"
#include "Visitor.h"

using namespace std;

/**
 * Draw digit
 *
 * @param graphics Graphics context to draw on
 */
void ItemDigit::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mDeclaration->Draw(graphics, GetRow(), GetCol());
}

/**
 * @return width of the declaration object
 */
double ItemDigit::GetWidth() const
{
    return mDeclaration->GetWidth();
}

/**
 * @return height of the declaration object
 */
double ItemDigit::GetHeight() const
{
    return mDeclaration->GetHeight();
}

/**
 *
 * @param visitor
 */
void ItemDigit::Accept(Visitor* visitor)
{
    visitor->VisitDigit(this);
}
