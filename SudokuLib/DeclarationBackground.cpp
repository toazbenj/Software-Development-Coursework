/**
 * @file DeclarationBackground.cpp
 *
 * @author Ethan Egger
 */

#include "pch.h"
#include "DeclarationBackground.h"
#include <wx/graphics.h>
#include <sstream>

using namespace std;

/**
 * Destructor
 */
DeclarationBackground::~DeclarationBackground()
{
}

/**
 * Load specific xml attributes
 *
 * @param node attribute strings
 */
void DeclarationBackground::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);
    node->GetAttribute(L"image"), wxString(mImage);
}

/**
 * Constructor
 *
 * @param node attribute strings
 */
DeclarationBackground::DeclarationBackground(wxXmlNode *node) : Declaration(node)
{
    wstringstream filename;
    filename << L"Images/" << node->GetAttribute(L"image");

    mDeclarationImage = std::make_unique<wxImage>(filename.str(), wxBITMAP_TYPE_ANY);
    mDeclarationBitmap = std::make_unique<wxBitmap>(*mDeclarationImage);
}

/**
 * Draw item from declaration
 *
 * @param graphics graphics context for playing area
 * @param row x coord
 * @param col y coord
 */
void DeclarationBackground::Draw(shared_ptr<wxGraphicsContext> graphics, double row, double col)
{
    double x = col * 48;
    double y = (row + 1) * 48 - GetHeight();

    graphics->DrawBitmap(*mDeclarationBitmap, x, y, GetWidth(), GetHeight());
}
