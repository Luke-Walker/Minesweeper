#ifndef TILE_H
#define TILE_H

#include <SDL.h>
#include <SDL_image.h>

#define TILE_SCALE 56

class Tile {
public:
    Tile();
    Tile(bool mine);
    Tile(int x, int y, int width, int height, bool mine);
    ~Tile();

    void renderTile(SDL_Renderer *renderer);

    void setValue(int value);
    int getValue();

    void setShown(bool shown);
    bool isShown();

    void toggleFlagged();
    void setFlagged(bool flagged);
    bool isFlagged();

    bool isMine();

    void setRect(SDL_Rect rect);
    SDL_Rect getRect();
private:
    int value; // -1 mine, 0 empty, n adjacent mines
    bool shown; // clicked or not
    bool flagged; // flagged or not
    SDL_Rect rect;
    SDL_Texture *texture;
};

#endif
