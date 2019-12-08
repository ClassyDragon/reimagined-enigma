#include "Tetramino.h"

// Default Constructor:
Tetramino::Tetramino() {
//    std::cout << "Constructed Tetramino\n";
}

// Constructor with type:
Tetramino::Tetramino(char type, sf::Texture* texture) : tetramino_type(type) {
    // Initial Rotation Value:
    current_rotation = 0;

    initBlockLayout();
    initBlockPositions(texture);
}

// Default Destructor:
Tetramino::~Tetramino() {
}

// Initialize Positions of blocks:
void Tetramino::initBlockLayout() {
    switch (tetramino_type) {
        case 'I': {
                      init_pos.resize(16);
                      init_pos = {
                          '_', '_', 'X', '_',
                          '_', '_', 'X', '_',
                          '_', '_', 'X', '_',
                          '_', '_', 'X', '_' 
                      };
                      block_positions = {2, 6, 10, 14};
                      break;
                  }
        case 'T': {
                      init_pos.resize(9);
                      init_pos = {
                          '_', 'X', '_',
                          'X', 'X', 'X',
                          '_', '_', '_' 
                      }; 
                      block_positions = {1, 3, 4, 5};
                      break;
                  }
        case 'J': {
                      init_pos.resize(9);
                      init_pos = {
                          'X', '_', '_',
                          'X', 'X', 'X',
                          '_', '_', '_'
                      }; 
                      block_positions = {0, 3, 4, 5};
                      break;
                  }
        case 'L': { 
                      init_pos.resize(9);
                      init_pos = {
                          '_', '_', 'X',
                          'X', 'X', 'X',
                          '_', '_', '_'
                      };
                      block_positions = {2, 3, 4, 5};
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
                      block_positions = {5, 6, 9, 10};
                      break;
                  }
        case 'S': {
                      init_pos.resize(9);
                      init_pos = {
                          '_', 'X', 'X',
                          'X', 'X', '_',
                          '_', '_', '_'
                      }; 
                      block_positions = {1, 2, 3, 4};
                      break;
                  }
        case 'Z': {
                      init_pos.resize(9);
                      init_pos = {
                          'X', 'X', '_',
                          '_', 'X', 'X',
                          '_', '_', '_'
                      }; 
                      block_positions = {0, 1, 4, 5};
                      break;
                  }
        default: {
                     init_pos.resize(9);
                     init_pos = {
                          'X', 'X', '_',
                          '_', 'X', '_',
                          '_', '_', 'X'
                     }; 
                     block_positions = {0, 1, 4, 5};
                 }
    }
}

void Tetramino::initBlockPositions(sf::Texture* texture) {

    for (int i = 0; i < 4; i++) {
        blocks.emplace_back(new Block());
    }
    for (auto& block : blocks) {
        block->setTexture(texture);
    }

    // Place Tetramino at the top-center of the field:
    vertical_position = 0;
    horizontal_position = field_width / 2 - (init_pos.size() == 9 ? 2 : 3);
    // I and O : 10 / 2 - 3 = 2
    // Else : 10 / 2 - 2 = 3

    switch (init_pos.size()) {
        case 9 : {
                     for (int i = 0; i < 4; i++) {
                         blocks[i]->set_screen_position(sf::Vector2f(
                                     horizontal_offset + 50 * (block_positions[i] % 3) + 50 * (horizontal_position),
                                     vertical_offset + 50 * (block_positions[i] / 3) + 50 * (vertical_position)
                                     ));
                         blocks[i]->set_field_position(sf::Vector2f(
                                     block_positions[i] % 3 + horizontal_position,
                                     block_positions[i] / 3 + vertical_position
                                     ));
                         int f = block_positions[i] % 3 + horizontal_position;
                         int g = block_positions[i] / 3 + vertical_position;
                     }
                     break;
                 }
        case 16 : {
                      for (int i = 0; i < 4; i++) {
                         blocks[i]->set_screen_position(sf::Vector2f(
                                     horizontal_offset + 50 * (block_positions[i] % 4) + 50 * (horizontal_position),
                                     vertical_offset + 50 * (block_positions[i] / 4) + 50 * (vertical_position)
                                     ));
                         blocks[i]->set_field_position(sf::Vector2f(
                                     block_positions[i] % 4 + horizontal_position,
                                     block_positions[i] / 4 + vertical_position
                                     ));
                      }
                      break;
                  }
    }
}

// Render Tetramino:
void Tetramino::render(sf::RenderWindow* window) {
    for (auto& i : blocks)
        i->render(window);
}

// Return character at the rotated index:
char Tetramino::get_block(int x, int y) {
    if (init_pos.size() == 9) {
        switch (current_rotation % 4) {
            case 0: // Return the unrotated character:
                return init_pos[x + ( 3 * y )]; 
            case 1: return init_pos[( 3 * x ) - y + 2];
            case 2: return init_pos[8 - ( 3 * y ) - x];
            case 3: return init_pos[6 - ( 3 * x ) + y];
            default: return 'E';
        }
    }
    else {
        switch (current_rotation % 4) {
            case 0: return init_pos[0 + ( 4 * y ) + x];
            case 1: return init_pos[3 + ( 4 * x ) - y];
            case 2: return init_pos[15 - ( 4 * y ) - x];
            case 3: return init_pos[12 - ( 4 * x ) + y];
            default: return 'E';
        }
    }
}

// Rotations:
void Tetramino::rotate_cw() {
    current_rotation = (current_rotation + 1) % 4;
    rotate_blocks();
    //std::cout << "Current Rotation: " << current_rotation << std::endl;
}

void Tetramino::rotate_ccw() {
    current_rotation = (current_rotation + 3) % 4;
    rotate_blocks();
}

void Tetramino::rotate_blocks() {
    int i = 0;
    for (auto& b : blocks) {
        int x;
        int y;
        switch (init_pos.size()) {
            case 9: {
                        x = block_positions[i] % 3;
                        y = block_positions[i] / 3;
                        switch (current_rotation % 4) {
                            case 0: {
                                        int pos = x + (3 * y);
                                        // x = block_positions[i] % 3
                                        // y = block_positions[i] / 3
                                        blocks[i]->set_field_position(sf::Vector2f((pos % 3) + horizontal_position, (pos / 3) + vertical_position));
                                        blocks[i]->set_screen_position(sf::Vector2f(
                                                    horizontal_offset + 50 * (pos % 3) + 50 * (horizontal_position),
                                                    vertical_offset + 50 * (pos / 3) + 50 * (vertical_position))
                                                );
                                        break;
                                    }
                            case 1: {
                                        int pos = (3 * x) - y + 2;
                                        blocks[i]->set_field_position(sf::Vector2f((pos % 3) + horizontal_position, (pos / 3) + vertical_position));
                                        blocks[i]->set_screen_position(sf::Vector2f(
                                                    horizontal_offset + 50 * (pos % 3) + 50 * (horizontal_position),
                                                    vertical_offset + 50 * (pos / 3) + 50 * (vertical_position))
                                                );
                                        break;
                                    }
                            case 2: {
                                        int pos = 8 - (3 * y) - x;
                                        blocks[i]->set_field_position(sf::Vector2f((pos % 3) + horizontal_position, (pos / 3) + vertical_position));
                                        blocks[i]->set_screen_position(sf::Vector2f(
                                                    horizontal_offset + 50 * (pos % 3) + 50 * (horizontal_position),
                                                    vertical_offset + 50 * (pos / 3) + 50 * (vertical_position))
                                                );
                                        break;
                                    }
                            case 3: {
                                        int pos = 6 - (3 * x) + y;
                                        blocks[i]->set_field_position(sf::Vector2f((pos % 3) + horizontal_position, (pos / 3) + vertical_position));
                                        blocks[i]->set_screen_position(sf::Vector2f(
                                                    horizontal_offset + 50 * (pos % 3) + 50 * (horizontal_position),
                                                    vertical_offset + 50 * (pos / 3) + 50 * (vertical_position))
                                                );
                                        break;
                                    }
                        }
                        break;
            }
            case 16: {
                        x = block_positions[i] % 4;
                        y = block_positions[i] / 4;
                        switch (current_rotation % 4) {
                            case 0: {
                                        int pos = x + (4 * y);
                                        // x = block_positions[i] % 3
                                        // y = block_positions[i] / 3
                                        blocks[i]->set_field_position(sf::Vector2f((pos % 4) + horizontal_position, (pos / 4) + vertical_position));
                                        blocks[i]->set_screen_position(sf::Vector2f(
                                                    horizontal_offset + 50 * (pos % 4) + 50 * (horizontal_position),
                                                    vertical_offset + 50 * (pos / 4) + 50 * (vertical_position))
                                                );
                                        break;
                                    }
                            case 1: {
                                        int pos = (4 * x) - y + 3;
                                        blocks[i]->set_field_position(sf::Vector2f((pos % 4) + horizontal_position, (pos / 4) + vertical_position));
                                        blocks[i]->set_screen_position(sf::Vector2f(
                                                    horizontal_offset + 50 * (pos % 4) + 50 * (horizontal_position),
                                                    vertical_offset + 50 * (pos / 4) + 50 * (vertical_position))
                                                );
                                        break;
                                    }
                            case 2: {
                                        int pos = 15 - (4 * y) - x;
                                        blocks[i]->set_field_position(sf::Vector2f((pos % 4) + horizontal_position, (pos / 4) + vertical_position));
                                        blocks[i]->set_screen_position(sf::Vector2f(
                                                    horizontal_offset + 50 * (pos % 4) + 50 * (horizontal_position),
                                                    vertical_offset + 50 * (pos / 4) + 50 * (vertical_position))
                                                );
                                        break;
                                    }
                            case 3: {
                                        int pos = 12 - (4 * x) + y;
                                        blocks[i]->set_field_position(sf::Vector2f((pos % 4) + horizontal_position, (pos / 4) + vertical_position));
                                        blocks[i]->set_screen_position(sf::Vector2f(
                                                    horizontal_offset + 50 * (pos % 4) + 50 * (horizontal_position),
                                                    vertical_offset + 50 * (pos / 4) + 50 * (vertical_position))
                                                );
                                        break;
                                    }
                        }
                        break;
                     }
        }
                i++;
    }
}

// Positional:
void Tetramino::move(sf::Vector2f offset) {
    
}

bool Tetramino::can_move_left() {
    // Check that each block can be moved:
    bool return_value = true;
    for (auto& b : blocks) {
        if (!b->can_move_left())
            return_value = false;
    }
    return return_value;
}

void Tetramino::move_left() {
    horizontal_position -= 1;
    for (auto& i : blocks) {
        i->move_screen_position(sf::Vector2f(-50, 0));
        i->move_left();
    }
    move(sf::Vector2f(-50, 0));
}

bool Tetramino::can_move_right() {
    bool return_value = true;
    for (auto& b : blocks) {
        if (!b->can_move_right())
            return_value = false;
    }
    return return_value;
}

void Tetramino::move_right() {
    horizontal_position += 1;
    for (auto& i : blocks) {
        i->move_screen_position(sf::Vector2f(50, 0));
        i->move_right();
        sf::Vector2f pos = i->get_field_position();
    }
    move(sf::Vector2f(50, 0));
}

// Get Field Position of block
sf::Vector2f Tetramino::get_field_position(int block, int rotation_offset) {
    // Value: X Position + (width * Y position) 
    int rotation = (current_rotation + rotation_offset) % 4;
    int fpos = block_positions[block];
    int x = fpos % 3;
    int y = fpos / 4;
    int pos;
    switch (rotation) {
        case 0: pos = (x + (3 * y));
                break;
        case 1: pos = ((3 * x) - y + 2);
                break;
        case 2: pos = (8 - (3 * y) - x);
                break;
        case 3: pos = (6 - (3 * x) + y);
                break;
    }
    return sf::Vector2f((pos % 3) + horizontal_position, (pos / 3) + vertical_position);
}

/*
 *
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
        */
