#include <iostream>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Tetris.h"

/* TODO:
 * 1. Add Music and Soud Effects.
 * 2. Add Sprint Mode.
 * 3. Add up-counting timer to show how long a player has taken.
 * 4. Add Pause Menu (With escape key)
 * 5. Allow player to play again or go back to the main menu upon winning or losing.
 */

int main() {
    TetrisGame tetris(1200, 1000, "Tetris");
    tetris.TetrisMain();
    return 0;
}
