#include "board.h"

Board::Board(int width, int height, int mines) {
    this->width = width;
    this->height = height;
    this->mines = mines;

    this->board = new Tile*[width];
    for (int i = 0; i < width; ++i) {
        this->board[i] = new Tile[height];

        for (int j = 0; j < height; ++j) {
            SDL_Rect rect;
            rect.x = i*TILE_SCALE;
            rect.y = j*TILE_SCALE;
            rect.w = TILE_SCALE;
            rect.h = TILE_SCALE;
            this->board[i][j].setRect(rect);
        }
    }

    // Place mines
    for (int i = 0; i < mines; ++i) {
        bool placing = true;
        while (placing) {
            int x = rand() % width;
            int y = rand() % height;
            Tile *tile = &this->board[x][y];

            if (tile->getValue() != -1) {
                tile->setValue(-1);
                placing = false;
            }
        }
    }

    updateBoard();
}

Board::~Board() {
    for (int i = 0; i < this->width; ++i)
        delete[] this->board[i];
    delete[] this->board;
}

void Board::updateBoard() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            Tile *tile = &board[i][j];
            if (tile->getValue() == -1) continue;

            /*
             *  1 2 3
             *  4 X 5
             *  6 7 8
             */

            int val = 0;
            bool top = i > 0;
            bool bottom = i < width-1;
            bool left = j > 0;
            bool right = j < height-1;
            if (top && left)
                val += board[i-1][j-1].isMine(); // 1
            if (top)
                val += board[i-1][j].isMine(); // 2
            if (top && right)
                val += board[i-1][j+1].isMine(); // 3
            if (left)
                val += board[i][j-1].isMine(); // 4
            if (right)
                val += board[i][j+1].isMine(); // 5
            if (bottom && left)
                val += board[i+1][j-1].isMine(); // 6
            if (bottom)
                val += board[i+1][j].isMine(); // 7
            if (bottom && right)
                val += board[i+1][j+1].isMine(); // 8

            tile->setValue(val);
        }
    }
}

void Board::renderBoard(SDL_Renderer *renderer) {
    for (int i = 0; i < this->width; ++i) {
        for (int j = 0; j < this->height; ++j) {
            this->board[i][j].renderTile(renderer);
        }
    }
}

void Board::chainTiles(int startX, int startY) {
    std::stack<int> xS;
    std::stack<int> yS;
    xS.push(startX);
    yS.push(startY);

    while (xS.size() > 0) {
        int x = xS.top(); xS.pop();
        int y = yS.top(); yS.pop();
        Tile *tile = this->getTile(x, y);

        if (tile->isShown()) continue;

        if (!tile->isMine()) tile->setShown(true);

        if (tile->getValue() == 0) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (x+dx < 0 || x+dx >= this->width) continue;

                for (int dy = -1; dy <= 1; ++dy) {
                    if (y+dy < 0 || y+dy >= this->height) continue;
                    if (dx == 0 && dy == 0) continue;
                    xS.push(x+dx);
                    yS.push(y+dy);
                }
            }
        }
    }
}

void Board::showMines() {
    for (int i = 0; i < this->width; ++i) {
        for (int j = 0; j < this->height; ++j) {
            Tile *tile = &this->board[i][j];

            if (tile->isMine()) tile->setShown(true);
        }
    }
}

Tile* Board::getTile(int x, int y) {
    return &this->board[x][y];
}

bool Board::isCompleted() {
    for (int i = 0; i < this->width; ++i) {
        for (int j = 0; j < this->height; ++j) {
            Tile *tile = &this->board[i][j];
            if (!tile->isMine() && !tile->isShown()) return false;
        }
    }
    return true;
}

int Board::getWidth() {
    return this->width;
}

int Board::getHeight() {
    return this->height;
}

int Board::getMines() {
    return this->mines;
}