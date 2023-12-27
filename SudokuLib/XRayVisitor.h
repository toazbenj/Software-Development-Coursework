/**
 * @file XRayVisitor.h
 * @author Ethan Egger
 *
 * Class defining a visitor to find the XRay item
 */

#ifndef PROJECT1_SUDOKULIB_XRAYVISITOR_H
#define PROJECT1_SUDOKULIB_XRAYVISITOR_H

#include "Visitor.h"
#include "memory"

/**
 * Visitor class for finding XRays
 *
 * visits items in sudoku looking for an XRay
 */
class XRayVisitor : public Visitor
{
private:
    /// Pointer to a XRay instance
    ItemXRay* mXRay;

public:
    void VisitXRay(ItemXRay* xRay) override;

    /**
     * Getter for the XRay
     * @return XRay object found by visitor
     */
    ItemXRay* GetXRay() const { return mXRay; }
};

#endif //PROJECT1_SUDOKULIB_XRAYVISITOR_H
