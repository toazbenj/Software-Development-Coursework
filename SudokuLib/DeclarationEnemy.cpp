/**
 * @file DeclarationEnemy.cpp
 *
 * @author Abhi Rao
 *
 */

#include "pch.h"
#include "DeclarationEnemy.h"
#include <wx/graphics.h>
#include <sstream>

using namespace std;


/**
 * Load specific xml attributes
 * @param node attribute strings
 */
void DeclarationEnemy::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);

    node->GetAttribute(L"image"), wxString(mImage);
    node->GetAttribute(L"direction"), wxString(mDirection);
}

/**
 * Constructor
 * @param node declaration node in XML file
 */
DeclarationEnemy::DeclarationEnemy(wxXmlNode *node) : Declaration(node)
{
    node->GetAttribute(L"target-x").ToDouble(&mTargetX);
    node->GetAttribute(L"target-y").ToDouble(&mTargetY);
    node->GetAttribute(L"width").ToInt(&mWidth);
    node->GetAttribute(L"height").ToInt(&mHeight);

    wstringstream filename;
    filename << L"Images/" << node->GetAttribute(L"image");

    mDeclarationImage = std::make_unique<wxImage>(filename.str(), wxBITMAP_TYPE_ANY);
    mDeclarationBitmap = std::make_unique<wxBitmap>(*mDeclarationImage);
    //XmlLoad(node);
    /*node->GetAttribute(L"width").ToInt(&mWidth);
    node->GetAttribute(L"height").ToInt(&mHeight);

    wstringstream filename1;
    filename1 << L"Images/" << node->GetAttribute(L"image1");
    wstringstream filename2;
    filename2 << L"Images/" << node->GetAttribute(L"image2");
    wstringstream filename3;
    filename3 << L"Images/" << node->GetAttribute(L"image3");
    wstringstream filename4;
    filename4 << L"Images/" << node->GetAttribute(L"image4");

    mImage1 = make_shared<wxImage>(filename1.str(), wxBITMAP_TYPE_ANY);
    mImage2 = make_shared<wxImage>(filename2.str(), wxBITMAP_TYPE_ANY);
    mImage3 = make_shared<wxImage>(filename3.str(), wxBITMAP_TYPE_ANY);
    mImage4 = make_shared<wxImage>(filename4.str(), wxBITMAP_TYPE_ANY);
    mBitmap1 = make_shared<wxBitmap>(*mImage1);
    mBitmap2 = make_shared<wxBitmap>(*mImage2);
    mBitmap3 = make_shared<wxBitmap>(*mImage3);
    mBitmap4 = make_shared<wxBitmap>(*mImage4);*/

}

/**
 * Make declaration from XML
 *
 * @param sudoku ptr to game
 * @param node xml attributes
 * @return digit of type given or movable
 */
shared_ptr<Item> DeclarationEnemy::Create(Sudoku *sudoku, wxXmlNode *node)
{
    /*auto name = node->GetName();

    if(name == L"enemy")
    {
        return std::make_shared<ItemEnemy>(sudoku, this);
    }*/
    auto item = std::make_shared<ItemEnemy>(sudoku, this);
    sudoku->SetEnemy(item);
    return item;
}

/**
 * Draw declaration
 *
 * @param graphics graphics context for playing area
 * @param row x coord
 * @param col y coord
 */
void DeclarationEnemy::Draw(shared_ptr<wxGraphicsContext> graphics, double row, double col)
{
    double width = GetWidth();
    double height = GetHeight();

    double x = col * GetWidth();
    double y = GetHeight() * (row - 1);

    graphics->DrawBitmap(*mDeclarationBitmap, x, y, width, height);
}
