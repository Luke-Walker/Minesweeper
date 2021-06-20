#include <iostream>
#include "window.h"

using namespace std;

int main(int argc, char *argv[]) {
    bool running = true;
    while (running) {
        int level;
        cout << endl;
        cout << "1. 8x8 (10 mines)" << endl;
        cout << "2. 16x16 (40 mines)" << endl;
        cout << "3. 16x30 (99 mines)" << endl;
        cout << "4. Custom" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter level: ";
        cin >> level;
        cin.ignore(100, '\n');

        if (level == 0) return 0;

        Board *board;
        if (level == 1) board = new Board(8, 8, 10);
        else if (level == 2) board = new Board(16, 16, 40);
        else if (level == 3) board = new Board(30, 16, 99);
        else if (level == 4) {
            int width, height, mines;

            cout << "Enter width: ";
            cin >> width;
            cin.ignore(100, '\n');

            cout << "Enter height: ";
            cin >> height;
            cin.ignore(100, '\n');

            cout << "Enter number of mines: ";
            cin >> mines;
            cin.ignore(100, '\n');

            board = new Board(width, height, mines);
        }
        else continue;

        Window window = Window(board);
        if (window.play()) { // win
            cout << "You win!" << endl;
        } else { // lose
            cout << "Better luck next time." << endl;
        }
    }

    return 0;
}
