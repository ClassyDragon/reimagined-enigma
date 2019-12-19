#include "Marathon.h"

Marathon::Marathon() {
}

Marathon::Marathon(sf::RenderWindow* window, int numPieces, int pieceOffset, int* savedScore) : GameState(window, numPieces, pieceOffset, savedScore) {
    field.setWinLines(200);
}
