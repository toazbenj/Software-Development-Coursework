/**
 * @file ItemDigitMovable.cpp
 * @author Peyton Nagher
 */

#include "pch.h"
#include "ItemDigitMovable.h"
#include "Visitor.h"

using namespace std;


/**
 *
 * @param visitor
 */
void ItemDigitMovable::Accept(Visitor *visitor)
{
    visitor->VisitDigitMovable(this);
}
