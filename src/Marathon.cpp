#include "Marathon.h"

Marathon::Marathon() {
    field.setWinLines(200);
}

Marathon::Marathon(sf::RenderWindow* window, int numPieces, int pieceOffset, int* savedScore) : GameState(window, numPieces, pieceOffset, savedScore) {
}
