/**
 * @file ContainerVisitor.cpp
 *
 * @author Ethan Egger, Peyton Nagher
 *
 * Go through items, release digits during sparty headbutt
 */

#include "pch.h"
#include "ContainerVisitor.h"
#include "ItemContainer.h"

using namespace std;

/**
 * Constructor
 *
 * @param x Target x coord for visitor
 * @param y Target y coord for visitor
 */
ContainerVisitor::ContainerVisitor(double x, double y)
{
    mTargetX = x;
    mTargetY = y;
}

/**
 * Visit a Container object
 *
 * @param container item to be visited
 */
void ContainerVisitor::VisitContainer(ItemContainer *container)
{
    auto minX = container->GetCol() * 48;
    auto maxX = container->GetCol() * 48 + container->GetWidth() / 2;
    auto minY = container->GetRow() * 48 - container->GetHeight();
    auto maxY = container->GetRow() * 48;
    if (minX <= mTargetX && maxX >= mTargetX && minY <= mTargetY && maxY >= mTargetY)
    {
        container->ReleaseDigits();
    }
}
