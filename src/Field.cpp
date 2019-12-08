#include "Field.h"

Field::Field() {
}

Field::Field(sf::RenderWindow* window) : window(window) {
    textures.insert(std::pair<char, sf::Texture>('r', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('p', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('y', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('g', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('o', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('b', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('c', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('w', sf::Texture()));

    // Load textures:
    textures['r'].loadFromFile("resources/red.png");
    textures['p'].loadFromFile("resources/purple.png");
    textures['y'].loadFromFile("resources/yellow.png");
    textures['g'].loadFromFile("resources/green.png");
    textures['o'].loadFromFile("resources/orange.png");
    textures['b'].loadFromFile("resources/blue.png");
    textures['c'].loadFromFile("resources/cyan.png");
    textures['w'].loadFromFile("resources/white.png");

    // Initialize keys:
    for (int i = 0; i < 3; i++)
        key_pressed[i] = 0;

    for (int i = 0; i < field_width; i++) {
        for (int j = 0; j < field_height; j++) {
            blocks[i][j] = new Block();
            blocks[i][j]->setTexture(&textures['w']);
            blocks[i][j]->set_screen_position(sf::Vector2f(50 + (50 * i), 50 + (50 * j)));
        }
    }


    movement_delay = new sf::Clock();

    init_rng();

    generate_piece(rng_bag.back());    
    rng_bag.pop_back();
}

Field::~Field() {
    for (int i = 0; i < field_width; i++)
        for (int j = 0; j < field_height; j++)
            delete blocks[i][j];
    delete current_piece;
    delete movement_delay;
}

void Field::render() {
    for (int i = 0; i < field_width; i++) {
        for (int j = 0; j < field_height; j++) {
            blocks[i][j]->render(window);
        }
    }
    current_piece->render(window);
}

void Field::update() {
    update_input();
    updatePiece();
}

void Field::update_input() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        move_left();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        move_right();
    }
    else {
        key_pressed[0] = 0;
        key_pressed[1] = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        if (key_pressed[2] == 0) {
            rotate_clockwise();
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        rotate_counter_clockwise();
    }
    else {
        key_pressed[2] = 0;
        key_pressed[3] = 0;
    }
}

void Field::updatePiece() {
    if (timeStill.getElapsedTime().asMilliseconds() >= 1000) {
        this->lockPiece();
    }
}

void Field::init_rng() {
    srand(time(NULL));
    std::vector<int> temp_bag;
    for (int i = 0; i < 7; i++) {
        temp_bag.push_back(i);
    }

    int tempint;
    while (!temp_bag.empty()) {
        tempint = rand() % temp_bag.size();
        rng_bag.push_back(temp_bag[tempint]);
        temp_bag.erase(temp_bag.begin() + tempint);
    }
}

void Field::generate_piece(int type) {
    switch (type) {
        case 0: {
                    current_piece = new Tetramino('S', &textures['r']);
                    break;
                }
        case 1: {
                    current_piece = new Tetramino('T', &textures['p']);
                    break;
                }
        case 2: {
                    current_piece = new Tetramino('J', &textures['b']);
                    break;
                }
        case 3: {
                    current_piece = new Tetramino('L', &textures['o']);
                    break;
                }
        case 4: {
                    current_piece = new Tetramino('Z', &textures['g']);
                    break;
                }
        case 5: {
                    current_piece = new Tetramino('O', &textures['y']);
                    break;
                }
        case 6: {
                    current_piece = new Tetramino('I', &textures['c']);
                    break;
                }
        default: {
                    current_piece = new Tetramino('I', &textures['r']);
                    break;
                 }
    }
}

void Field::set_window(sf::RenderWindow* window) {
    this->window = window;
}

// Current Piece Functions:
bool Field::can_move_left() {
    if (current_piece->can_move_left())
        return true;
    return false;
}

void Field::move_left() {   
    
    if (can_move_left()) {
        if (key_pressed[0] == 0) {
            movement_delay->restart();
            current_piece->move_left();
            key_pressed[0] = 1;
        }
        if (key_pressed[0] == 1 && movement_delay->getElapsedTime().asMilliseconds() >= move_time_1) {
            current_piece->move_left();
            key_pressed[0] = 2;
        }
        if (key_pressed[0] == 2 && movement_delay->getElapsedTime().asMilliseconds() >= move_time_2) {
            current_piece->move_left();
            key_pressed[0] = 3;
            movement_delay->restart();
        }
        if (key_pressed[0] == 3 && movement_delay->getElapsedTime().asMilliseconds() >= move_time_3) {
            current_piece->move_left();
            movement_delay->restart();
        }
    }
    
}

bool Field::can_move_right() {
    if (current_piece->can_move_right())
        return true;
    return false;
}

void Field::move_right() {

    if (can_move_right()) {
        if (key_pressed[1] == 0) {
            movement_delay->restart();
            current_piece->move_right();
            key_pressed[1] = 1;
        }
        else if (key_pressed[1] == 1 && movement_delay->getElapsedTime().asMilliseconds() >= move_time_1) {
            current_piece->move_right();
            key_pressed[1] = 2;
        }
        else if (key_pressed[1] == 2 && movement_delay->getElapsedTime().asMilliseconds() >= move_time_2) {
            current_piece->move_right();
            key_pressed[1] = 3;
            movement_delay->restart();
        }
        else if (key_pressed[1] == 3 && movement_delay->getElapsedTime().asMilliseconds() >= move_time_3) {
            current_piece->move_right();
            movement_delay->restart();
        }
    }
}

void Field::move_down() {
    if (current_piece->can_move_down()) {
        current_piece->move_down();
        timeStill.restart();
    }
}

void Field::hard_drop() {
}

void Field::soft_drop() {
}

bool Field::can_rotate_clockwise() {
    // Check that after rotation, all blocks will be within the field and not intersect other blocks.
    // Get field position of all blocks in piece
    bool can_rotate = true;
    for (int i = 0; i < 4; i++) {
        sf::Vector2f rotated_pos = current_piece->get_field_position(i, 1);
        if (rotated_pos.x >= field_width || rotated_pos.x < 0 || rotated_pos.y >= field_height) {
            can_rotate = false;
        }
    }
    return can_rotate;
}

void Field::rotate_clockwise() {
    if (can_rotate_clockwise() && key_pressed[2] == 0) {
        key_pressed[2] = 1;
        current_piece->rotate_cw();
    }
}

bool Field::can_rotate_counter_clockwise() {
    bool can_rotate = true;
    for (int i = 0; i < 4; i++) {
        sf::Vector2f rotated_pos = current_piece->get_field_position(i, 3);
        if (rotated_pos.x >= field_width || rotated_pos.x < 0 || rotated_pos.y >= field_height) {
            can_rotate = false;
        }
    }
    return can_rotate;
}

void Field::rotate_counter_clockwise() {
    if (can_rotate_counter_clockwise() && key_pressed[3] == 0) {
        key_pressed[3] = 1;
        current_piece->rotate_ccw();
    }
}

void Field::lockPiece() {
    // Iterate through all blocks in current piece
    // Find the field index that corresponds to that piece's position
    // Transfer the attributes
    for (int i = 0; i < 4; i++) {
        sf::Vector2f fpos = current_piece->get_field_position(i, 0);
//        std::cout << fpos.x << ", " << fpos.y << std::endl;
        Block* b = current_piece->getBlock(i);
        this->blocks[(int)(fpos.x)][(int)(fpos.y)]->setTexture(b->getTexture());
//        this->blocks[(int)(fpos.x)][(int)(fpos.y)]->set_screen_position(b->get_screen_position());
//        this->blocks[(int)(fpos.x)][(int)(fpos.y)]->set_field_position(b->get_field_position());
    }
    delete current_piece;
    generate_piece(rng_bag.back());    
    rng_bag.pop_back();
    timeStill.restart();
}
