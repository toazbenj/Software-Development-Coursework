/**
 * @file ItemDigitVisitor.h
 * @author Peyton Nagher
 *
 * Checks if sparty can interact with digit
 */

#ifndef PROJECT1_SUDOKULIB_ITEMDIGITVISITOR_H
#define PROJECT1_SUDOKULIB_ITEMDIGITVISITOR_H

#include "Visitor.h"
#include "Sudoku.h"
#include "ItemDigit.h"
#include "ItemContainer.h"

/// Functionality for eating and regurgitating
class ItemDigitVisitor : public Visitor
{
private:
    /// sparty position
    double mSpartyX;
    /// sparty position
    double mSpartyY;
    /// minimum interaction distance
    double mDistanceThreshold;
    /// interaction flag
    bool mItemDigitNearby;

public:
    /**
     * Constructor
     * @param spartyX sparty pos
     * @param spartyY sparty pos
     * @param distanceThreshold interaction distance
     */
    ItemDigitVisitor(double spartyX, double spartyY, double distanceThreshold)
        : mSpartyX(spartyX), mSpartyY(spartyY), mDistanceThreshold(distanceThreshold),
            mItemDigitNearby(false) {}

    void VisitDigit(ItemDigit* itemDigit) override;
    /**
     * Get interaction flag
     * @return bool
     */
    bool ItemDigitNearby() const { return mItemDigitNearby; }
};

#endif //PROJECT1_SUDOKULIB_ITEMDIGITVISITOR_H
