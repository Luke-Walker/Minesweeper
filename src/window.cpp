#include "window.h"

Window::Window(Board *board) {
    SDL_Init(SDL_INIT_VIDEO);

    std::string title = "Minesweeper | " + std::to_string(board->getWidth()) + "x" + std::to_string(board->getHeight()) + " (" + std::to_string(board->getMines()) + " Mines)";
    this->window = SDL_CreateWindow(title.c_str(), SCREEN_WIDTH/2, SCREEN_HEIGHT/2, board->getWidth()*TILE_SCALE, board->getHeight()*TILE_SCALE, 0);
    if (!this->window) {
        std::cout << "Error: Could not create window." << std::endl;
        exit(1);
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    this->board = board;
}

Window::~Window() {
    SDL_DestroyWindow(this->window);
    IMG_Quit();
    SDL_Quit();

    delete this->board;
}

bool Window::play() {
    bool end = false;
    bool result = false;
    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e) > 0) {
            switch (e.type) {
                case SDL_QUIT:
                    return false;
                case SDL_MOUSEBUTTONDOWN: {
                    if (end) return result;

                    int mouseX = e.motion.x;
                    int mouseY = e.motion.y;
                    int x = mouseX/TILE_SCALE;
                    int y = mouseY/TILE_SCALE;
                    Tile *tile = this->board->getTile(x, y);

                    switch (e.button.button) {
                        case SDL_BUTTON_LEFT:
                            if (!tile->isShown()) {
                                // safety flag prevention
                                if (!tile->isFlagged()) {
                                    if (tile->isMine()) {
                                        board->showMines();
                                        end = true;
                                        result = false;
                                    } else {
                                        this->board->chainTiles(x, y);

                                        if (this->board->isCompleted()) {
                                            end = true;
                                            result = true;
                                        }
                                    }
                                }
                            }

                            break;
                        case SDL_BUTTON_RIGHT:
                            if (!tile->isShown()) {
                                tile->toggleFlagged();
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
        }

        render();

        //if (this->board->isCompleted()) return true;
    }
    return false;
}

void Window::render() {
    SDL_RenderClear(this->renderer);
    this->board->renderBoard(this->renderer);
    SDL_RenderPresent(this->renderer);
}
