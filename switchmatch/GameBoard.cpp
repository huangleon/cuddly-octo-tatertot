#include "GameBoard.h"
namespace game {
    ////////////////////////////////////////////////////////////////////////////////
    // implementation of Tile
    Tile::Tile(int color)
        : mColor(color)
          , mMatched(false)
    {
    }
    ////////////////////////////////////////////////////////////////////////////////
    // implementation of GameBoard
    void GameBoard::generateTiles()
    {
        // generate tiles randomly
    }
    void GameBoard::swapTile(int x1, int y1, int x2, int y2)
    {
        if ( !is_adjacent(x1, y1, x2, y2) )
            return;
    }
    void GameBoard::updateMatch(int x, int y)
    {
        int low, high, left, right;
        low = high = y;
        left = right = x;
        // horizontal check
        for (bool changed = true; changed;)
        {
            changed = false;
            if ( left > 0 && color_equals(left - 1, y, x, y) )
            {
                --left;
                changed = true;
            }
            if ( right < BOARD_SIZE - 1 && color_equals(right + 1, y, x, y) )
            {
                ++right;
                changed = true;
            }
        }
        // check change count >= 3
        if ( right - left + 1 >= 3
        // vertical check
    }
} // end namespace game
