/**
 * @file ContainerVisitor.h
 *
 * @author Ethan Egger, Peyton Nagher
 *
 * This class represents a visitor for a cauldron or pumpkin
 */

#include "Visitor.h"

#ifndef PROJECT1_SUDOKULIB_CONTAINERVISITOR_H
#define PROJECT1_SUDOKULIB_CONTAINERVISITOR_H

/// Inheritance from visitor class
class ContainerVisitor : public Visitor
{
private:
    /// movement value from sparty x
    double mTargetX;
    /// movement value from sparty y
    double mTargetY;

public:
    ContainerVisitor(double x, double y);
    void VisitContainer(ItemContainer *container) override;
};

#endif //PROJECT1_SUDOKULIB_CONTAINERVISITOR_H
