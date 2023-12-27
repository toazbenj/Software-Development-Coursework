/**
 * @file DeclarationDigit.cpp
 *
 * @author Ethan Egger, Peyton Nagher
 *
 */

#include "pch.h"
#include "DeclarationDigit.h"
#include "ItemDigitGiven.h"
#include <wx/graphics.h>
#include <sstream>

using namespace std;

/**
 * Destructor
 */
DeclarationDigit::~DeclarationDigit()
{
}

/**
 * Load specific xml attributes
 * @param node attribute strings
 */
void DeclarationDigit::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);
    node->GetAttribute(L"image"), wxString(mImage);
    node->GetAttribute(L"value").ToInt(&mValue);
}

/**
 * Constructor
 * @param node attribute strings
 */
DeclarationDigit::DeclarationDigit(wxXmlNode *node) : Declaration(node) {
    wstringstream filename;
    filename << L"Images/" << node->GetAttribute(L"image");

    mDeclarationImage = std::make_unique<wxImage>(filename.str(), wxBITMAP_TYPE_ANY);
    mDeclarationBitmap = std::make_unique<wxBitmap>(*mDeclarationImage);
    XmlLoad(node);
}

/**
 * Make item from xml declaration
 * @param sudoku ptr to game
 * @param node xml attributes
 * @return digit of type given or movable
 */
shared_ptr<Item> DeclarationDigit::Create(Sudoku *sudoku, wxXmlNode *node)
{
    auto name = node->GetName();

    if(name == L"given")
    {
        return std::make_shared<ItemDigitGiven>(sudoku, this);
    }
    else
    {
        return std::make_shared<ItemDigitMovable>(sudoku, this);
    }
}

/**
 * Draw item from declaration
 * @param graphics graphics context for playing area
 * @param row x coord
 * @param col y coord
 */
void DeclarationDigit::Draw(shared_ptr<wxGraphicsContext> graphics, double row, double col)
{
    graphics->DrawBitmap(*mDeclarationBitmap, col * GetWidth(), row * GetHeight(), GetWidth(), GetHeight());
}
