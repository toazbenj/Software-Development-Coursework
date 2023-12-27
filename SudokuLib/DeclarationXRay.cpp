/**
 * @file DeclarationXRay.cpp
 *
 * @author Ethan Egger
 *
 */

#include "pch.h"
#include "DeclarationXRay.h"
#include <wx/graphics.h>
#include <sstream>

using namespace std;

/**
 * Destructor
 */
DeclarationXRay::~DeclarationXRay()
{
}

/**
 * Load specific xml attributes
 * @param node attribute strings
 */
DeclarationXRay::DeclarationXRay(wxXmlNode *node) : Declaration(node)
{
    node->GetAttribute(L"capacity").ToDouble(&mCapacity);

    wstringstream filename;
    filename << L"Images/" << node->GetAttribute(L"image");

    mDeclarationImage = std::make_unique<wxImage>(filename.str(), wxBITMAP_TYPE_ANY);
    mDeclarationBitmap = std::make_unique<wxBitmap>(*mDeclarationImage);
}

/**
 * Draw item from declaration
 * @param graphics graphics context for playing area
 * @param row x coord
 * @param col y coord
 */
void DeclarationXRay::Draw(const shared_ptr<wxGraphicsContext>& graphics, double row, double col)
{
    double x = (col * GetWidth()) / 3.0;
    double y = (row + 1) * 48 - GetHeight();
    graphics->DrawBitmap(*mDeclarationBitmap, x, y, GetWidth(), GetHeight());
}