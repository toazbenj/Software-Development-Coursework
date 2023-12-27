/**
 * @file Sudoku.cpp
 * @author Peyton Nagher, Ben Toaz
 *
 * Equivalent to generic game class in examples plus virtual pixels
 */

#include "pch.h"
#include "Sudoku.h"
#include "Item.h"
#include "Popup.h"
#include "SudokuVisitor.h"
#include "XRayVisitor.h"
#include "RegurgitateVisitor.h"
#include <wx/graphics.h>
#include "SolveVisitor.h"
#include <numeric>
#include "DigitResetVisitor.h"
using namespace std;


/**
 * Constructor for a Sudoku board
 */
Sudoku::Sudoku()
{
    mScoreBoard = std::make_shared<ScoreBoard>();
    mPopupManager = std::make_shared<PopupManager>(this);
    Load(L"Levels/level1.xml", 1);

    std::random_device rd;
    mRandom.seed(rd());
}

/**
 * Clears all items in the Sudoku game
 */
void Sudoku::Clear()
{
    mItems.clear();
}

/**
 * Adds an item to the Sudoku Game
 *
 * @param item
 */
void Sudoku::Add(std::shared_ptr<Item>& item)
{
    double c = round(item->GetCol());
    double r = round(item->GetRow());

    item->SetLocation(c, r);
    mItems.push_back(item);
}

/**
 * Brings Sparty to the front of all elements on the screen
 */
void Sudoku::MoveSpartyFront()
{
    auto pos = find(mItems.begin(), mItems.end(), mSparty);
    mItems.erase(pos);
    mItems.push_back(mSparty);
}

/**
 * Brings enemy to the front of all elements on the screen
 */
void Sudoku::MoveEnemyFront()
{
    auto pos = find(mItems.begin(), mItems.end(), mEnemy);
    mItems.erase(pos);
    mItems.push_back(mEnemy);
}

/**
 * Checks to see if there is an item at a specified location
 *
 * @param x
 * @param y
 * @return either an item or a nullptr
 */
shared_ptr<Item> Sudoku::HitTest(double x, double y)
{
    for (auto item : mItems)
    {
        if (item->HitTest(x, y))
        {
            return item;
        }
    }

    return nullptr;
}

/**
 * Removes a digit item from the Sudoku game
 *
 * @param digit
 * @return either an item or a nullptr
 */
shared_ptr<ItemDigitMovable> Sudoku::PopDigit(ItemDigitMovable *digit)
{
    for (auto itr = mItems.begin(); itr != mItems.end(); ++itr)
    {
        if (itr->get() == digit)
        {
            auto item = std::static_pointer_cast<ItemDigitMovable>(*itr);
            mItems.erase(itr);
            return item;
        }
    }

    return nullptr;
}

/**
 * Loads a new Sudoku level based on XML file input
 *
 * @param filename What level metadata to load
 * @param levelNum What level number to load
 */
void Sudoku::Load(const wxString &filename, const int& levelNum)
{
    mEnemy = nullptr;
    mFreeze = true;
    mLevelNumber = levelNum;
    wxXmlDocument xmlDoc;

    if (!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load level file");
        return;
    }

    Clear();

    auto root = xmlDoc.GetRoot();
    auto declarations = root->GetChildren();
    auto game = declarations->GetNext();
    auto items = game->GetNext();

    mLevel = make_shared<Level>(root);
    auto child = items->GetChildren();

    for (; child; child=child->GetNext())
    {
        XmlItem(child);
    }

    mPopupManager->Load();
}

/**
 * Handle a node of type item.
 *
 * @param node XML node
 */
void Sudoku::XmlItem(wxXmlNode *node)
{
    auto id = node->GetAttribute(L"id");
    auto declaration = mLevel->GetDeclaration(id);
    auto item = declaration->Create(this, node);

    item->SetLevel(mLevel.get());
    Add(item);
    item->XmlLoad(node);
}

/**
 * Draw the game
 *
 * @param graphics Graphics device to draw on
 * @param width Width of the window
 * @param height Height of the window
 */
void Sudoku::OnDraw(std::shared_ptr<wxGraphicsContext>& graphics, const int& width, const int& height)
{
    int pixelWidth = (mLevel->GetWidth()) * (mLevel->GetTileWidth());
    int pixelHeight = (mLevel->GetHeight()) * (mLevel->GetTileHeight());

    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;

    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();
    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    for (auto item : mItems)
    {
        item->Draw(graphics);
    }

    mPopupManager->Draw(graphics);

    if (mFreeze)
    {
        mScoreBoard->Reset();
    }
    else
    {
        mScoreBoard->Draw(graphics);
    }

    graphics->PopState();
}

/**
* Handle a mouse click by converting coords
* from regular screen to virtual pixels,
* moving sparty item as needed
*
* @param x X location clicked on
* @param y Y location clicked on
*/
void Sudoku::OnLeftDown(const int& x, const int& y)
{
    int pixelWidth = (mLevel->GetWidth()) * (mLevel->GetTileWidth());
    int pixelHeight = (mLevel->GetHeight()) * (mLevel->GetTileHeight());

    double oX = (x - mXOffset) / mScale;
    double oY = (y - mYOffset) / mScale;

    if (!mFreeze)
    {
        mSparty->SetTarget(oX, oY, true, pixelWidth, pixelHeight);
        if(mEnemy != nullptr)
        {
            mEnemy->SetTarget(oX,oY,true, pixelWidth, pixelHeight);
        }
    }
}

/**
 * Handles the keyboard input for eating
 */
void Sudoku::OnSpaceDown()
{
    if (!mFreeze)
    {
        mSparty->MoveMouth("eat");
    }
}

/**
 * Handles the keyboard input for regurgitating
 *
 * @param targetNum
 */
void Sudoku::OnNumKeyDown(const int& targetNum)
{
    XRayVisitor xVisitor;
    Accept(&xVisitor);

    RegurgitateVisitor visitor(targetNum, GetLevel()->GetTileWidth(), GetLevel()->GetBoardBounds());
    auto xRay = xVisitor.GetXRay();
    xRay->ContentsAccept(&visitor);

    if (visitor.GetDigit() != nullptr && !mFreeze)
    {
        mSparty->MoveMouth("regurgitate", targetNum);
    }
}

/**
 * Handles keyboard input for headbutting
 */
void Sudoku::OnBDown()
{
    if (!mFreeze)
    {
        mSparty->Headbutt();
    }
}

/**
 * Handle updates for animation
 *
 * @param elapsed Time since last update
 */
void Sudoku::Update(const double& elapsed)
{
    if (!mFreeze)
    {
        mSparty->Update(elapsed);
        if(mEnemy != nullptr)
        {
            mEnemy->Update(elapsed);
        }
    }

    mScoreBoard->Update(elapsed);
    mPopupManager->Update(elapsed);

    SudokuVisitor visitor(mLevel->GetBoardBounds());
    this->Accept(&visitor);

    vector<int> answer = visitor.GetAnswer();
    int sum = accumulate(answer.begin(),answer.end(), 0);
    if (sum == 324)
    {
        CheckSolution(answer);
    }
}

/**
 * Calls respective Accept function for a visitor on an item
 *
 * @param visitor
 */
void Sudoku::Accept(Visitor *visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Compare user's answer to the solution, game mechanics for right and wrong answers
 *
 * @param currentAnswer vector of digits to compare with solution
 */
void Sudoku::CheckSolution(const vector<int>& currentAnswer)
{
    vector<int> answer = this->GetLevel()->GetSolution();
    bool win = currentAnswer == answer;

    GetPopupManager()->GetWinLoss()->Initialize(win);
}

/**
 * Load the next level in the sequence,
 * based on win state
 *
 * @param win whether the current level was won
 */
void Sudoku::AdvanceLevel(bool win)
{
    if (win)
    {
        if(mLevelNumber == 0)
        {
            this->Load("Levels/level1.xml",1);
        }
        else if (mLevelNumber == 1)
        {
            this->Load("Levels/level2.xml",2);
        }
        else if ((mLevelNumber == 2 )|| (mLevelNumber == 3))
        {
            this->Load("Levels/level3.xml", 3);
        }
    }
    else
    {
        if (mLevelNumber == 0)
        {
            this->Load("Levels/level0.xml",0);
        }
        else if (mLevelNumber == 1)
        {
            this->Load("Levels/level1.xml",1);
        }
        else if (mLevelNumber == 2)
        {
            this->Load("Levels/level2.xml",2);
        }
        else
        {
            this->Load("Levels/level3.xml",3);
        }
    }
}

/**
 * Solve the current level with given XML
 */
void Sudoku::Solve()
{
    vector<int> boardBounds = mLevel->GetBoardBounds();
    int rowLowerBound = boardBounds[0];
    int colLowerBound = boardBounds[1];
    vector<int> answer = mLevel->GetSolution();

    for (int row = rowLowerBound; row < rowLowerBound+9;row++)
    {
        for (int col = colLowerBound; col < colLowerBound+9;col++)
        {
            int solutionIndex = (col-colLowerBound)+(row-rowLowerBound)*9;
            int value = answer[solutionIndex];
            SolveVisitor visitor(row, col, value);
            this->Accept(&visitor);
        }
    }

    DigitResetVisitor visitorReset;
    this->Accept(&visitorReset);
}

/**
 * Returns a digit at a specific location
 *
 * @param col Target column
 * @param row Target row
 * @return Item or nullptr
 */
shared_ptr<Item> Sudoku::GetDigitAt(int col, int row)
{
    for (auto item : mItems)
    {
        if (item->GetCol() == col && item->GetRow() == row)
        {
            return item;
        }
    }
    return nullptr;
}
