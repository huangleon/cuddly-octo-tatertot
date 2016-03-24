#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

namespace game {
    ////////////////////////////////////////////////////////////////////////////////
    // Definition of Tile
    class Tile {
        private:
            enum {
                COLOR1 = 0,
                COLOR2,
                COLOR3,
                COLOR4,
                COLOR5,

                COLOR_COUNT
            };
        private:
            // tile color
            int mColor;
            // status of whether this tile is matched with adjacent tile and
            // will be clear in next stage
            bool mMatched;
        public:
            explicit Tile(int color);

            void setMatched(bool matched) { mMatched = matched; }
            bool getMatched() const { return mMatched; }
            int getColor() const { return mColor; }
    };
    ////////////////////////////////////////////////////////////////////////////////
    // Definition of GameBoard
    class GameBoard {
        private:
            enum {
                // board size 8 x 8
                BOARD_SIZE = 8,

            };
            Tile mTiles[BOARD_SIZE][BOARD_SIZE];
            // check whether 2 tiles are adjacent to each other
            bool is_adjacent(int x1, int y1, int x2, int y2) const
            {
                return ((x1 == x2) && (y1 - y2 == 1 || y1 - y2 == -1))
                    || ((y1 == y2) && (x1 - x2 == 1 || x1 - x2 == -1));
            }
            bool color_equals(int x1, int y1, int x2, int y2) const
            {
                return mTiles[x1][y1].getColor() == mTiles[x2][y2].getColor();
            }
        public:
            // generate tiles randomly
            void generateTiles();
            // swap the tile between (x1, y1) and (x2, y2)
            void swapTile(int x1, int y1, int x2, int y2);
            // update the match status from the start tile (x, y)
            void updateMatch(int x, int y);
    };
} // end namespace game
#endif // end of __GAMEBOARD_H__

