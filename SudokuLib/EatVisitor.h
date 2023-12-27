/**
 * @file EatVisitor.h
 *
 * @author Ben Toaz
 *
 * Visit sudoku, move digits sparty eats to xray
 */

#ifndef PROJECT1_SUDOKULIB_EATVISITOR_H
#define PROJECT1_SUDOKULIB_EATVISITOR_H

#include "Visitor.h"
#include "ItemXRay.h"
#include "ItemSparty.h"

/// Sparty eating fuctionality
class EatVisitor: public Visitor
{
private:
    /// ptr to digit being eaten
    ItemDigitMovable* mEatenDigit = nullptr;
    /// sparty movement coord
    double mTargetX;
    /// sparty movement coord
    double mTargetY;
public:
    EatVisitor(double x, double y);
    virtual void VisitDigitMovable(ItemDigitMovable *digit) override;
    virtual void VisitXRay(ItemXRay* xray) override;
    void SendToXRay();
};

#endif //PROJECT1_SUDOKULIB_EATVISITOR_H
