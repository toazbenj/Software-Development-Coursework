/**
 * @file Item.cpp
 * @author Peyton Nagher, Ben Toaz
 *
 * Implementation file for Item class
 */

#include "pch.h"
#include "Item.h"

using namespace std;

/**
 * Constructor
 * @param PSudoku
 */
Item::Item(Sudoku *PSudoku) : mSudoku(PSudoku)
{
}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode *Item::XmlSave(wxXmlNode *node)
{
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");
    node->AddChild(itemNode);

    itemNode->AddAttribute(L"id", wxString(mID));
    itemNode->AddAttribute(L"col", wxString::FromDouble(mCol));
    itemNode->AddAttribute(L"row", wxString::FromDouble(mRow));

    return itemNode;
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"id", wxString(mID));
    node->GetAttribute(L"col").ToDouble(&mCol);
    node->GetAttribute(L"row").ToDouble(&mRow);
}

/**
 * Draw item
 * @param graphics Graphics context to draw on
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
}

/**
 * Check if item is overlaid with point
 * @param x coord
 * @param y coord
 * @return bool flag
 */
bool Item::HitTest(double x, double y)
{
    double testX = x - GetCol() * GetLevelTileWidth();
    double testY = y - GetRow() * GetLevelTileHeight();

    // Test to see if x, y are in the image
    if(testX < 0 || testY < 0 || testX >= GetWidth() || testY >= GetHeight())
    {
        // We are outside the image
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * Set item's image
 * @param filename string
 */
void Item::SetImage(const std::wstring &filename)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage);
}



