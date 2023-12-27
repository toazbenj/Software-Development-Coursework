/**
 * @file Declaration.h
 *
 * @author Peyton Nagher
 *
 * Base class for all declaration objects in the game
 */

#ifndef PROJECT1_SUDOKULIB_DECLARATION_H
#define PROJECT1_SUDOKULIB_DECLARATION_H

#include <wx/xml/xml.h>

class Sudoku;
class Item;

/// Base class for declarations with image data
class Declaration
{
private:
    /// id for xml entry
    wxString mID = "";
    /// width value for xml entry
    double mWidth = 0;
    /// height value for xml entry
    double mHeight = 0;

public:
    Declaration() = delete;
    Declaration(const Declaration &) = delete;
    ~Declaration();

    Declaration(wxXmlNode *node=nullptr);

    /**
     * Drawing virtual function
     * @param row coord
     * @param col coord
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext>, double row, double col) {};
    /**
     * Item making virtual function
     * @param sudoku game ptr
     * @param node xml attributes
     * @return item of whichever type
     */
    virtual std::shared_ptr<Item> Create(Sudoku *sudoku, wxXmlNode *node) = 0;

    /**
     * Loading virtual base function
     * @param node xml attributes
     */
    virtual void XmlLoad(wxXmlNode *node){};

    /**
     *
     * @return type string
     */
    wxString& GetId() { return mID; }
    /**
     *
     * @return image width
     */
    virtual double GetWidth() const { return mWidth; }
    /**
     *
     * @return image height
     */
    virtual double GetHeight() const { return mHeight; }

    /**
     *
     * @param id set type string
     */
    void SetID(wxString &id) { mID = id; }
    /**
     *
     * @param width length of image
     */
    void SetWidth(double width) { mWidth = width; }
    /**
     *
     * @param height height of image
     */
    void SetHeight(double height) { mHeight = height; }
};

#endif //PROJECT1_SUDOKULIB_DECLARATION_H
