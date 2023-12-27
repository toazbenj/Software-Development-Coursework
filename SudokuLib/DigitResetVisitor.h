/**
 * @file DigitResetVisitor.h
 *
 * @author Ben Toaz
 *
 * Visitor to set all digit isMoved flags back to false after solve
 */

#ifndef ACTIONSUDOKU_SUDOKULIB_DIGITRESETVISITOR_H
#define ACTIONSUDOKU_SUDOKULIB_DIGITRESETVISITOR_H

#include "Visitor.h"
#include "ItemDigitMovable.h"

/// Inheritance from visitor class
class DigitResetVisitor: public Visitor
{
public:
    virtual void VisitDigitMovable(ItemDigitMovable* digit) override;

};

#endif //ACTIONSUDOKU_SUDOKULIB_DIGITRESETVISITOR_H
