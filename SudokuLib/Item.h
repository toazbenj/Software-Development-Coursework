/**
 * @file Item.h
 * @author Peyton Nagher, Ben Toaz
 *
 * Base class for all item objects in the game
 */

#ifndef PROJECT1_SUDOKULIB_ITEM_H
#define PROJECT1_SUDOKULIB_ITEM_H

#include <wx/xml/xml.h>
#include "Level.h"
#include "Declaration.h"

class Visitor;
class Sudoku;

///Base class for all game objects
class Item
{
protected:
    /**
     *     constructor, look at SudokuBoard class for
     *     example of how to use with inheritance
     */
    Item(Sudoku *PSudoku);
    /// Pointer to the current level
    Level* mLevel = nullptr;
private:

    /// the sudoku system class the item belongs to
    Sudoku *mSudoku = nullptr;

    /// The image for this item
    std::unique_ptr<wxImage> mItemImage = nullptr;

    /// The bitmap for this item
    std::unique_ptr<wxBitmap> mItemBitmap = nullptr;
    /// string type identifier
    wxString mID = "";
    /// y coord in virtual pixels
    double  mCol = 0;
    /// x coord in virtual pixels
    double  mRow = 0;

public:
    /// Copy constructor (disabled)
    Item(const Item &) = delete;
    /// Assignment operator (disabled)
    void operator=(const Item &) = delete;

    virtual wxXmlNode *XmlSave(wxXmlNode *node);
    virtual void XmlLoad(wxXmlNode *node);

    /**
     * Set string type
     * @param id string
     */
    void SetID(wxString &id) { mID = id; }

    /**
     * Set coord
     * @param col coord
     */
    void SetCol(double col) { mCol = col; }
    /**
      * Set coord
      * @param row coord
      */
    void SetRow(double row) { mRow = row; }
    /**
      * Get string type
      * @return string
      */
    wxString GetID() const { return mID; }
    /**
     * Get coord
     * @return coord
     */
    double GetCol() const { return mCol; }
    /**
      * Get coord
      * @return coord
      */
    double GetRow() const { return mRow; }
    /**
     * Get image size
     * @return size
     */
    virtual double GetWidth() const { return mItemImage->GetWidth(); }
    /**
      * Get image size
      * @return size
      */
    virtual double GetHeight() const { return mItemImage->GetHeight(); }
    /**
     * Get ptr to game
     * @return game ptr
     */
    Sudoku* GetSudoku() const {return mSudoku;}
    /**
     * Get image
     * @return image
     */
    wxBitmap GetBitmap() const {return *mItemBitmap;}
    /**
     * Set coords
     * @param c x coord
     * @param r y coord
     */
    virtual void SetLocation(double c, double r) { mCol = c; mRow = r; }

    void SetImage(const std::wstring &filename);

    /**
    * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(Visitor* visitor) = 0;


     virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);
     virtual bool HitTest(double x, double y);

    /**
     * Set the current level
     * @param level ptr to current level
     */
    void SetLevel(Level* level) { mLevel = level; }
    /**
     * Return size of virtual pixels
     * @return int
     */
    int GetLevelTileWidth() const { return mLevel->GetTileWidth(); }
    /**
     * Return size of virtual pixels
     * @return int
     */
    int GetLevelTileHeight() const { return mLevel->GetTileHeight(); }
};

#endif //PROJECT1_SUDOKULIB_ITEM_H