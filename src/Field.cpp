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

    GameOver = false;
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
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        hardDrop();
    }
    else {
        keyPressed[0] = 0;
        keyPressed[1] = 0;
        keyPressed[4] = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        if (keyPressed[2] == 0) {
            rotate(1);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        if (keyPressed[3] == 0) {
            rotate(3);
        }
    }
    else {
        keyPressed[2] = 0;
        keyPressed[3] = 0;
    }
}

void Field::updatePiece() {
    if (timeStill.getElapsedTime().asMilliseconds() >= 20000) {
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
        sf::Vector2i fpos = currentPiece->get_field_position(i, 0);
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
        sf::Vector2i fpos = currentPiece->get_field_position(i, 0);
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
        sf::Vector2i fpos = currentPiece->get_field_position(i, 0);
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
    if (keyPressed[4] == 0) {
        keyPressed[4] = 1;
        std::set<int> indexes;
        for (int i = 0; i < 4; i++) {
            sf::Vector2i position = currentPiece->get_field_position(i, 0);
            int x = position.x;
            int y = position.y;
            while (y < field_height - 1) {
                if (!blocks[x][y + 1]->isSolid()) {
                    y++;
                }
                else {
                    break;
                }
            }
            indexes.insert(y);
        }
        // indexes.end() contains the largest, indexes.begin() contains the lowest
        for (int i = 0; i < *indexes.begin(); i++) {
            moveDown();
        }
        lockPiece();
    }
}

void Field::softDrop() {
}

int Field::canRotate(int r) {
    // 1: Rotate in place
    // 2: Rotate down 1
    // 3: Rotate up 1
    // 4: Rotate left 1
    // 5: Rotate Right 1
    // -1: Can't rotate
    // Check that after rotation, all blocks will be within the field and not intersect other blocks.
    // Get field position of all blocks in piece
    std::vector<sf::Vector2i> rotated_pos(4);
    rotated_pos[0] = (currentPiece->get_field_position(0, r));
    rotated_pos[1] = (currentPiece->get_field_position(1, r));
    rotated_pos[2] = (currentPiece->get_field_position(2, r));
    rotated_pos[3] = (currentPiece->get_field_position(3, r));
    bool valid = true;
    // Case 1: In place
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y >= field_height || rotated_pos[i].x >= field_width || rotated_pos[i].x < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x][rotated_pos[i].y]->isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 1;
    }
    valid = true;
    // Case 2: Down
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y + 1 >= field_height || rotated_pos[i].x >= field_width || rotated_pos[i].x < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x][rotated_pos[i].y + 1]->isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 2;
    valid = true;
    // Case 3: Up
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y - 1 >= field_height || rotated_pos[i].x >= field_width || rotated_pos[i].x < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x][rotated_pos[i].y - 1]->isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 3;
    valid = true;
    // Case 4: Left
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y >= field_height || rotated_pos[i].x - 1 >= field_width || rotated_pos[i].x - 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y]->isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 4;
    valid = true;
    // Case 5: Right
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y >= field_height || rotated_pos[i].x + 1 >= field_width || rotated_pos[i].x + 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y]->isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 5;
    valid = true;
    // Case 8: Down Left
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y + 1 >= field_height || rotated_pos[i].x - 1 >= field_width || rotated_pos[i].x - 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y + 1]->isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 8;
    valid = true;
    // Case 9: Down Right
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y >= field_height + 1 || rotated_pos[i].x + 1 >= field_width || rotated_pos[i].x + 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y + 1]->isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 9;
    valid = true;
    // Case 6: Up Left
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y - 1 >= field_height || rotated_pos[i].x - 1 >= field_width || rotated_pos[i].x - 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y - 1]->isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 6;
    valid = true;
    // Case 7: Up Right
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y - 1 >= field_height || rotated_pos[i].x + 1 >= field_width || rotated_pos[i].x + 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y - 1]->isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 7;
    return -1;
}

void Field::rotate(int r) {
    int offset = canRotate(r);
    if (offset != -1 && keyPressed[2] == 0 && keyPressed[3] == 0) {
        keyPressed[2] = 1;
        keyPressed[3] = 1;
        currentPiece->rotate(r, offset);
    }
}

void Field::lockPiece() {
    // Iterate through all blocks in current piece
    // Find the field index that corresponds to that piece's position
    // Transfer the attributes
    std::set<int> linesAffected;
    bool dropDown = true;
    for (int i = 0; i < 4; i++) {
        sf::Vector2i fpos = currentPiece->get_field_position(i, 0);
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
        sf::Vector2i fpos = currentPiece->get_field_position(i, 0);
        Block* b = currentPiece->getBlock(i);
        this->blocks[fpos.x][fpos.y]->setTexture(b->getTexture());
        this->blocks[fpos.x][fpos.y]->setSolid();
        linesAffected.insert(fpos.y);
    }
    delete currentPiece;
    if (linesAffected.find(0) != linesAffected.end()) {
        GameOver = true;
    }
    else {
        clearLines(linesAffected);
        generatePiece(rngBag.back());    
        rngBag.pop_back();
        timeStill.restart();
    }
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
    switch (toClear.size()) {
        case 1: *Score = *Score + 100;
                break;
        case 2: *Score = *Score + 300;
                break;
        case 3: *Score = *Score + 500;
                break;
        case 4: *Score = *Score + 800;
    }
    *LinesCleared = *LinesCleared + toClear.size();
    this->fScore->setString(std::to_string(*Score));
    this->fLinesCleared->setString(std::to_string(*LinesCleared));
}

// Game Over Check:
bool Field::isGameOver() {
    return GameOver;
}

// Set Score and Line Cleared Ref:
void Field::setScoreRef(int* Score) {
    this->Score = Score;
}

void Field::setLinesClearedRef(int* LinesCleared) {
    this->LinesCleared = LinesCleared;
}

void Field::setTextRef(sf::Text* fScore, sf::Text* fLinesCleared) {
    this->fScore = fScore;
    this->fLinesCleared = fLinesCleared;
}
