
#include "Tetris.h"

// Default Constructor:
Tetramino::Tetramino() {
}

// Constructor with type:
Tetramino::Tetramino(char type) {
    switch (type) {
        case 'I':
        case 'T':
        case 'J':
        case 'L':
        case 'O':
        case 'S':
        case 'Z':
        default:
    }
}

// Default Destructor:
Tetramino::~Tetramino() {
}
