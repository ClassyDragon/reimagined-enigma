
#include "Tetramino.h"

// Default Constructor:
//Tetramino::Tetramino() {
//    std::cout << "Constructed Tetramino\n";
//}

// Constructor with type:
Tetramino::Tetramino(char type) {
    // Initial Rotation Value:
    current_rotation = 0;

    switch (type) {
        case 'I': {
                      init_pos.resize(16);
                      init_pos = {
                          '_', '_', 'X', '_',
                          '_', '_', 'X', '_',
                          '_', '_', 'X', '_',
                          '_', '_', 'X', '_' 
                      };
                      break;
                  }
        case 'T': {
                      init_pos.resize(9);
                      init_pos = {
                          '_', 'X', '_',
                          'X', 'X', 'X',
                          '_', '_', '_' 
                      };
                      break;
                  }
        case 'J': {
                      init_pos.resize(9);
                      init_pos = {
                          'X', '_', '_',
                          'X', 'X', 'X',
                          '_', '_', '_'
                      };
                      break;
        case 'L': { 
                      init_pos.resize(9);
                      init_pos = {
                          '_', '_', 'X',
                          'X', 'X', 'X',
                          '_', '_', '_'
                      };
                      break;
                  }
        case 'O': {
                      init_pos.resize(16);
                      init_pos = {
                          '_', '_', '_', '_',
                          '_', 'X', 'X', '_',
                          '_', 'X', 'X', '_',
                          '_', '_', '_', '_'
                      };
                      break;
                  }
        case 'S': {
                      init_pos.resize(9);
                      init_pos = {
                          '_', 'X', 'X',
                          'X', 'X', '_',
                          '_', '_', '_'
                      };
                      break;
                  }
        case 'Z': {
                      init_pos.resize(9);
                      init_pos = {
                          'X', 'X', '_',
                          '_', 'X', 'X',
                          '_', '_', '_'
                      };
                      break;
                  }
        default: {
                     init_pos.resize(9);
                     init_pos = {
                          'X', 'X', '_',
                          '_', 'X', 'X',
                          '_', '_', '_'
                     };
                 }
                  }
    }
}

// Default Destructor:
Tetramino::~Tetramino() {
}

// Return character at the rotated index:
char Tetramino::get_block(int x, int y) {
    if (init_pos.size() == 9) {
        switch (current_rotation % 4) {
            case 0: {
                        // Return the unrotated character:
                        return init_pos[x + ( 3 * y )]; 
                    }
            case 1: {
                        return init_pos[( 3 * x ) - y + 2];
                    }
            case 2: {
                        return init_pos[8 - ( 3 * y ) - x];
                    }
            case 3: {
                        return init_pos[6 - ( 3 * x ) + y];
                    }
            default: {
                         return 'E';
                     }
        }
    }
    else {
        switch (current_rotation % 4) {
            case 0: {
                        return init_pos[0 + ( 4 * y ) + x];
                    }
            case 1: {
                        return init_pos[3 + ( 4 * x ) - y];
                    }
            case 2: {
                        return init_pos[15 - ( 4 * y ) - x];
                    }
            case 3: {
                        return init_pos[12 - ( 4 * x ) + y];
                    }
            default: {
                         return 'E';
                     }
        }
    }
}

// Rotations:
void Tetramino::rotate_cw() {
    current_rotation = (current_rotation + 1) % 4;
}

void Tetramino::rotate_ccw() {
    current_rotation = (current_rotation + 3) % 4;
}
