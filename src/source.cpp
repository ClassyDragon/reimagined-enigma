
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tetris.h"

int main() {
    TetrisGame* tetris;
    tetris = new TetrisGame(1200, 1000, "Tetris");
    tetris->run();
    return 0;
}
