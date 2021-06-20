#ifndef WINDOW_H
#define WINDOW_H

#include "board.h"
#include <iostream>
#include <string>
#include <SDL.h>

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT 1080

class Window {
public:
    Window(Board *board);
    ~Window();

    bool play();
    void render();
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    Board *board;
};

#endif
