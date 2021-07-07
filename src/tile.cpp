#include "tile.h"

SDL_Surface *TEXTURES[] = {
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/hidden.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/flagged.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/mine.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/empty.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/adj1.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/adj2.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/adj3.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/adj4.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/adj5.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/adj6.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/adj7.png"),
        IMG_Load("C:\\Users\\luker\\OneDrive\\Documents\\Projects\\Minesweeper\\src\\textures/adj8.png")
};

Tile::Tile(): Tile(false) {}

Tile::Tile(bool mine): Tile(0, 0, 0, 0, mine) {}

Tile::Tile(int x, int y, int width, int height, bool mine) {
    this->rect.x = x;
    this->rect.y = y;
    this->rect.w = width;
    this->rect.h = height;

    this->texture = nullptr;

    this->value = 0 - mine; // -1 mine, 0 not mine
    this->shown = false;
    this->flagged = false;
}

Tile::~Tile() {
    if (this->texture != nullptr) SDL_DestroyTexture(this->texture);
}

void Tile::renderTile(SDL_Renderer *renderer) {
    if (this->texture != nullptr) SDL_DestroyTexture(this->texture);

    SDL_Surface *surface = nullptr;
    if (this->shown) {
        if (this->isMine()) surface = TEXTURES[2];
        else surface = TEXTURES[this->value + 3];
    } else {
        if (flagged) surface = TEXTURES[1];
        else surface = TEXTURES[0];
    }

    if (surface == nullptr) return;

    this->texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderCopy(renderer, this->texture, nullptr, &this->rect);
}

void Tile::setValue(int value) {
    this->value = value;
}

int Tile::getValue() {
    return this->value;
}

void Tile::setShown(bool shown) {
    this->shown = shown;
}

bool Tile::isShown() {
    return this->shown;
}

void Tile::toggleFlagged() {
    this->flagged = !this->flagged;
}

void Tile::setFlagged(bool flagged) {
    this->flagged = flagged;
}

bool Tile::isFlagged() {
    return this->flagged;
}

bool Tile::isMine() {
    return this->value == -1;
}

void Tile::setRect(SDL_Rect rect) {
    this->rect = rect;
}

SDL_Rect Tile::getRect() {
    return this->rect;
}