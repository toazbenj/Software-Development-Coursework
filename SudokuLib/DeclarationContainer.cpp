/**
 * @file DeclarationContainer.cpp
 *
 * @author Ethan Egger
 *
 */

#include "pch.h"
#include "DeclarationContainer.h"
#include <wx/graphics.h>
#include <sstream>

using namespace std;

/**
 * Destructor
 */
DeclarationContainer::~DeclarationContainer()
{
}

/**
 * Load specific xml attributes
 * @param node attribute strings
 */
void DeclarationContainer::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);
    // move to derived classes
    node->GetAttribute(L"image"), wxString(mImage);
    node->GetAttribute(L"capacity").ToInt(&mCapacity);
}

/**
 * Constructor
 *
 * @param node attribute strings
 */
DeclarationContainer::DeclarationContainer(wxXmlNode *node) : Declaration(node)
{
    wstringstream ffilename;
    ffilename << L"Images/" << node->GetAttribute(L"front");
    mFrontImage = std::make_unique<wxImage>(ffilename.str(), wxBITMAP_TYPE_ANY);
    mFrontBitmap = std::make_unique<wxBitmap>(*mFrontImage);

    wstringstream filename;
    filename << L"Images/" << node->GetAttribute(L"image");

    mDeclarationImage = std::make_unique<wxImage>(filename.str(), wxBITMAP_TYPE_ANY);
    mDeclarationBitmap = std::make_unique<wxBitmap>(*mDeclarationImage);
}

/**
 * Draw item from declaration back
 *
 * @param graphics graphics context for playing area
 * @param row x coord
 * @param col y coord
 */
void DeclarationContainer::Draw(shared_ptr<wxGraphicsContext> graphics, double row, double col)
{
    double x = col * 48;
    double y = (row + 1) * 48 - GetHeight();
    graphics->DrawBitmap(*mDeclarationBitmap, x, y, GetWidth(), GetHeight());
}

/**
 * Draw item from declaration front
 *
 * @param graphics graphics context for playing area
 * @param row x coord
 * @param col y coord
 */
void DeclarationContainer::DrawFront(std::shared_ptr<wxGraphicsContext> graphics, double row, double col)
{
    double x = col * 48;
    double y = (row + 1) * 48 - GetHeight();
    graphics->DrawBitmap(*mFrontBitmap, x, y, GetWidth(), GetHeight());
}
