/**
 * @file Level.h
 * @author Peyton Nagher
 *
 * Class that describes a level
 */

#ifndef PROJECT1_SUDOKULIB_LEVEL_H
#define PROJECT1_SUDOKULIB_LEVEL_H

#include "Declaration.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <wx/xml/xml.h>

/// Class to handle specifics of each level
class Level
{
private:
    /// vector of characters encoding the solution to the sudoku game
    std::vector<int> mSolution;
    /// Vector of game declaration objects
    std::unordered_map<wxString, std::shared_ptr<Declaration>> mDeclarations;
    /// Width of level area
    int mWidth;
    /// Height of level area
    int mHeight;
    /// Width of a tile
    int mTileWid;
    /// Height of a tile
    int mTileHit;
    /// limits of sudoku board
    int mColLowerBound = 100;
    /// row limit for sudoku board
    int mRowLowerBound = 100;

public:
    Level(const Level &) = delete;
    void operator=(const Level &) = delete;
    Level(wxXmlNode *levelNode);
    void XmlDeclaration(wxXmlNode *node);
    void Clear();
    std::unordered_map<wxString, std::shared_ptr<Declaration>> GetDeclarations();
    std::vector<int> GetSolution();
    /**
     * Get image info for all items
     * @param id string identifier
     * @return declaration
     */
    std::shared_ptr<Declaration> GetDeclaration(const wxString &id) { return mDeclarations[id]; };
    /**
     * Get size
     * @return int
     */
    int GetWidth() const { return mWidth; }
    /**
      * Get size
      * @return int
      */
    int GetHeight() const { return mHeight; }
    /**
      * Get size
      * @return int
      */
    int GetTileWidth() const { return mTileWid; }
    /**
      * Get size
      * @return int
      */
    int GetTileHeight() const { return mTileHit; }
    /**
      * Get size of sudoku board
      * @return vector of ints
      */
    std::vector<int> GetBoardBounds() { return { mRowLowerBound, mColLowerBound }; }
};

#endif //PROJECT1_SUDOKULIB_LEVEL_H