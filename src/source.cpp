#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Tetris.h"

int main() {
    TetrisGame tetris(1200, 1000, "Tetris");
    tetris.TetrisMain();
    return 0;
}
