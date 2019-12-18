#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Tetris.h"

/* TODO:
 * 1. Add Music and Soud Effects.
 */

int main() {
    TetrisGame tetris(1200, 1000, "Tetris");
    tetris.TetrisMain();
    return 0;
}
