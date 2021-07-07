#ifndef BOARD_H
#define BOARD_H

#include <cstdlib>
#include <iostream>
#include <stack>
#include "tile.h"

class Board {
public:
    Board(int width, int height, int mines);
    ~Board();

    void updateBoard();
    void renderBoard(SDL_Renderer *renderer);
    void chainTiles(int startX, int startY);
    void showMines();

    Tile* getTile(int x, int y);

    bool isCompleted();

    int getWidth();
    int getHeight();
    int getMines();
private:
    int width, height, mines;
    Tile **board;
};

#endif