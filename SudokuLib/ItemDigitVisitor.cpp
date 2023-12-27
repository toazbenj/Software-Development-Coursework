/**
 * @file ItemDigitVisitor.cpp
 * @author Peyton Nagher
 */

#include "pch.h"
#include "ItemDigitVisitor.h"

using namespace std;


/**
 * Visitor function to check if a digit is nearby
 *
 * @param itemDigit
 */
void ItemDigitVisitor::VisitDigit(ItemDigit* itemDigit)
{
    double itemX = itemDigit->GetCol();
    double itemY = itemDigit->GetRow();
    double distance = std::sqrt(std::pow(mSpartyX - itemX, 2) + std::pow(mSpartyY - itemY, 2));

    if (distance <= mDistanceThreshold)
    {
        mItemDigitNearby = true;
    }
}