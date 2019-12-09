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
        keyPressed[i] = 0;

    for (int i = 0; i < field_width; i++) {
        for (int j = 0; j < field_height; j++) {
            blocks[i][j] = new Block();
            blocks[i][j]->setTexture(&textures['w']);
            blocks[i][j]->set_screen_position(sf::Vector2f(50 + (50 * i), 50 + (50 * j)));
        }
    }


    movementDelay = new sf::Clock();

    init_rng();

    generatePiece(rngBag.back());    
    rngBag.pop_back();
}

Field::~Field() {
    for (int i = 0; i < field_width; i++)
        for (int j = 0; j < field_height; j++)
            delete blocks[i][j];
    delete currentPiece;
    delete movementDelay;
}

void Field::render() {
    for (int i = 0; i < field_width; i++) {
        for (int j = 0; j < field_height; j++) {
            blocks[i][j]->render(window);
        }
    }
    currentPiece->render(window);
}

void Field::update() {
    updateInput();
    updatePiece();
}

void Field::updateInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        moveLeft();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        moveRight();
    }
    else {
        keyPressed[0] = 0;
        keyPressed[1] = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        if (keyPressed[2] == 0) {
            rotateClockwise();
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        rotateCounterClockwise();
    }
    else {
        keyPressed[2] = 0;
        keyPressed[3] = 0;
    }
}

void Field::updatePiece() {
    if (timeStill.getElapsedTime().asMilliseconds() >= 1000) {
        this->lockPiece();
    }
    if (rngBag.size() == 0) {
        init_rng();
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
        rngBag.push_back(temp_bag[tempint]);
        temp_bag.erase(temp_bag.begin() + tempint);
    }
}

void Field::generatePiece(int type) {
    switch (type) {
        case 0: {
                    currentPiece = new Tetramino('S', &textures['r']);
                    break;
                }
        case 1: {
                    currentPiece = new Tetramino('T', &textures['p']);
                    break;
                }
        case 2: {
                    currentPiece = new Tetramino('J', &textures['b']);
                    break;
                }
        case 3: {
                    currentPiece = new Tetramino('L', &textures['o']);
                    break;
                }
        case 4: {
                    currentPiece = new Tetramino('Z', &textures['g']);
                    break;
                }
        case 5: {
                    currentPiece = new Tetramino('O', &textures['y']);
                    break;
                }
        case 6: {
                    currentPiece = new Tetramino('I', &textures['c']);
                    break;
                }
        default: {
                    currentPiece = new Tetramino('I', &textures['r']);
                    break;
                 }
    }
}

void Field::setWindow(sf::RenderWindow* window) {
    this->window = window;
}

// Current Piece Functions:
bool Field::canMoveLeft() {
    for (int i = 0; i < 4; i++) {
        sf::Vector2i fpos = static_cast<sf::Vector2i>(currentPiece->get_field_position(i, 0));
        if (fpos.x == 0) {
            return false;
        }
        else if (this->blocks[fpos.x - 1][fpos.y]->isSolid()) {
            return false;
        }
    }
    return true;
}

void Field::moveLeft() {   
    
    if (canMoveLeft()) {
        if (keyPressed[0] == 0) {
            movementDelay->restart();
            currentPiece->moveLeft();
            keyPressed[0] = 1;
        }
        if (keyPressed[0] == 1 && movementDelay->getElapsedTime().asMilliseconds() >= move_time_1) {
            currentPiece->moveLeft();
            keyPressed[0] = 2;
        }
        if (keyPressed[0] == 2 && movementDelay->getElapsedTime().asMilliseconds() >= move_time_2) {
            currentPiece->moveLeft();
            keyPressed[0] = 3;
            movementDelay->restart();
        }
        if (keyPressed[0] == 3 && movementDelay->getElapsedTime().asMilliseconds() >= move_time_3) {
            currentPiece->moveLeft();
            movementDelay->restart();
        }
    }
    
}

bool Field::canMoveRight() {
    for (int i = 0; i < 4; i++) {
        sf::Vector2i fpos = static_cast<sf::Vector2i>(currentPiece->get_field_position(i, 0));
        if (fpos.x == field_width - 1) {
            return false;
        }
        else if (this->blocks[fpos.x + 1][fpos.y]->isSolid()) {
            return false;
        }
    }
    return true;
}

void Field::moveRight() {

    if (canMoveRight()) {
        if (keyPressed[1] == 0) {
            movementDelay->restart();
            currentPiece->moveRight();
            keyPressed[1] = 1;
        }
        else if (keyPressed[1] == 1 && movementDelay->getElapsedTime().asMilliseconds() >= move_time_1) {
            currentPiece->moveRight();
            keyPressed[1] = 2;
        }
        else if (keyPressed[1] == 2 && movementDelay->getElapsedTime().asMilliseconds() >= move_time_2) {
            currentPiece->moveRight();
            keyPressed[1] = 3;
            movementDelay->restart();
        }
        else if (keyPressed[1] == 3 && movementDelay->getElapsedTime().asMilliseconds() >= move_time_3) {
            currentPiece->moveRight();
            movementDelay->restart();
        }
    }
}

void Field::moveDown() {
    bool moveDown = true;
    for (int i = 0; i < 4; i++) {
        sf::Vector2i fpos = static_cast<sf::Vector2i>(currentPiece->get_field_position(i, 0));
        if (fpos.y == field_height - 1) {
            moveDown = false;
            break;
        }
        else if (this->blocks[fpos.x][fpos.y + 1]->isSolid()) {
            moveDown = false;
            break;
        }
    }
    if (moveDown) {
        currentPiece->moveDown();
        timeStill.restart();
    }
}

void Field::hardDrop() {
}

void Field::softDrop() {
}

bool Field::canRotateClockwise() {
    // Check that after rotation, all blocks will be within the field and not intersect other blocks.
    // Get field position of all blocks in piece
    for (int i = 0; i < 4; i++) {
        sf::Vector2i rotated_pos = static_cast<sf::Vector2i>(currentPiece->get_field_position(i, 1));
        if (rotated_pos.x >= field_width || rotated_pos.x < 0 || rotated_pos.y >= field_height) {
            return false;
        }
        else if (blocks[rotated_pos.x][rotated_pos.y]->isSolid()){
            return false;
        }
    }
    return true;
}

void Field::rotateClockwise() {
    if (canRotateClockwise() && keyPressed[2] == 0) {
        keyPressed[2] = 1;
        currentPiece->rotate_cw();
    }
}

bool Field::canRotateCounterClockwise() {
    for (int i = 0; i < 4; i++) {
        sf::Vector2i rotated_pos = static_cast<sf::Vector2i>(currentPiece->get_field_position(i, 3));
        if (rotated_pos.x >= field_width || rotated_pos.x < 0 || rotated_pos.y >= field_height) {
            return false;
        }
        else if (blocks[rotated_pos.x][rotated_pos.y]->isSolid()){
            return false;
        }
    }
    return true;
}

void Field::rotateCounterClockwise() {
    if (canRotateCounterClockwise() && keyPressed[3] == 0) {
        keyPressed[3] = 1;
        currentPiece->rotate_ccw();
    }
}

void Field::lockPiece() {
    // Iterate through all blocks in current piece
    // Find the field index that corresponds to that piece's position
    // Transfer the attributes
    std::set<int> linesAffected;
    bool dropDown = true;
    for (int i = 0; i < 4; i++) {
        sf::Vector2i fpos = static_cast<sf::Vector2i>(currentPiece->get_field_position(i, 0));
        if (fpos.y == field_height - 1) {
            dropDown = false;
            break;
        }
        else if (this->blocks[fpos.x][fpos.y + 1]->isSolid()) {
            dropDown = false;
            break;
        }
    }
    if (dropDown) {
        timeStill.restart();
        return;
    }
    for (int i = 0; i < 4; i++) {
        sf::Vector2i fpos = static_cast<sf::Vector2i>(currentPiece->get_field_position(i, 0));
        Block* b = currentPiece->getBlock(i);
        this->blocks[fpos.x][fpos.y]->setTexture(b->getTexture());
        this->blocks[fpos.x][fpos.y]->setSolid();
        linesAffected.insert(fpos.y);
    }
    delete currentPiece;
    clearLines(linesAffected);
    generatePiece(rngBag.back());    
    rngBag.pop_back();
    timeStill.restart();
}

void Field::clearLines(std::set<int>& linesAffected) {
    std::set<int> toClear;
    for (auto& line : linesAffected) {
        bool lineCleared = true;
        for (int i = 0; i < field_width; i++) {
            if (!blocks[i][line]->isSolid()) {
                lineCleared = false;
                break;
            }
        }
        if (lineCleared) {
            // Remove line from set:
            toClear.insert(line);
        }
    }
    for (auto& line : toClear) {
        for (int i = line - 1; i >= 0; i--) {
            for (int j = 0; j < field_width; j++) {
                blocks[j][i + 1]->setTexture(blocks[j][i]->getTexture());
                blocks[j][i + 1]->setSolid(blocks[j][i]->isSolid());
                blocks[j][i]->setTexture(&textures['w']);
                blocks[j][i]->setEmpty();
            }
        }
    }
}
