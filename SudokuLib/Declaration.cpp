/**
 * @file Declaration.cpp
 * @author Peyton Nagher
 *
 * Implementation file for Declaration class
 */

#include "pch.h"
#include "Declaration.h"
#include <wx/graphics.h>

using namespace std;

/**
 * Destructor
 */
Declaration::~Declaration()
{
}

/**
 * Constructor, initializes member variables
 *
 * @param node xml collection of attributes
 */
Declaration::Declaration(wxXmlNode *node)
{
    mID = node->GetAttribute(L"id");
    node->GetAttribute(L"width").ToDouble(&mWidth);
    node->GetAttribute(L"height").ToDouble(&mHeight);
}
