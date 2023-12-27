/**
 * @file SpartyVisitor.h
 * @author Peyton Nagher
 *
 * Class to represent a visitor for Sparty that will be used for moving digits
 */

#ifndef PROJECT1_SUDOKULIB_SPARTYVISITOR_H
#define PROJECT1_SUDOKULIB_SPARTYVISITOR_H

#include "Visitor.h"
#include "Sudoku.h"
#include "ItemDigit.h"
#include "ItemContainer.h"

class ItemDigit;

/// Digit moving functionality
class SpartyVisitor : public Visitor
{
private:
    /// pointer to a cauldron/pumpkin container
    ItemContainer* mContainer;
    /// item pointer to
    std::shared_ptr<Item> mItem;

public:
    /**
     * Constructor
     * @param item item being moved
     * @param container contains item
     */
    SpartyVisitor(std::shared_ptr<Item> item, ItemContainer* container) : mItem(item), mContainer(container) {}
    void VisitSudoku(Sudoku*);
    virtual void VisitDigit(std::shared_ptr<Item>, ItemContainer*, bool);
};

#endif //PROJECT1_SUDOKULIB_SPARTYVISITOR_H
