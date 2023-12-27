/**
 * @file Visitor.h
 *
 * @author Peyton Nagher, Ben Toaz
 *
 * Visitor Base Class
 */

#ifndef PROJECT1_SUDOKULIB_VISITOR_H
#define PROJECT1_SUDOKULIB_VISITOR_H

class Item;
class ItemDigit;
class ItemDigitMovable;
class ItemContainer;
class ItemXRay;
class ItemSparty;

/**
 * Base visitor class
 */
class Visitor
{
public:
    /**
     * Destructor for a visitor
     */
    virtual ~Visitor() {}

    /**
     * Visit an item object
     * @param item item to be visited
     */
    virtual void VisitItem(Item* item) {}

    /**
     * Visit a digit object
     * @param digit digit to be visited
     */
    virtual void VisitDigit(ItemDigit* digit) {}

    /**
     * Visit a moveable digit object
     * @param digit digit to be visited
     */
    virtual void VisitDigitMovable(ItemDigitMovable* digit) {}

    /**
     * Visit a container object
     * @param container item to be visited
     */
    virtual void VisitContainer(ItemContainer* container) {}

    /**
     * Visit an xray object
     * @param xray item to be visited
     */
    virtual void VisitXRay(ItemXRay* xray) {}
};

#endif //PROJECT1_SUDOKULIB_VISITOR_H
