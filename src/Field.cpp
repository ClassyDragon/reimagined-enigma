#include "Field.h"

Field::Field() {
}

Field::Field(sf::RenderWindow* window) : window(window) {

    initTextures();
    initKeys();

    for (int i = 0; i < field_width; i++) {
        for (int j = 0; j < field_height; j++) {
            blocks[i][j] = Block();
            blocks[i][j].setTexture(&textures['w']);
            blocks[i][j].set_screen_position(sf::Vector2f(50 + (50 * i), 50 + (50 * j)));
        }
    }

    initRNG();

    generatePiece(rngBag.back());    
    rngBag.pop_back();
    initGhostPiece();

    GameOver = false;
    initNextPieceQueue();
    initLineClearAnimations();
}

Field::~Field() {
    delete currentPiece;
}

// Init Functions:
void Field::initTextures() {
    // Init Textures:
    textures.insert(std::pair<char, sf::Texture>('r', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('p', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('y', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('g', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('o', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('b', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('c', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('w', sf::Texture()));
    textures.insert(std::pair<char, sf::Texture>('a', sf::Texture())); // Alpha (clear)

    // Load textures:
    textures['r'].loadFromFile("resources/red.png");
    textures['p'].loadFromFile("resources/purple.png");
    textures['y'].loadFromFile("resources/yellow.png");
    textures['g'].loadFromFile("resources/green.png");
    textures['o'].loadFromFile("resources/orange.png");
    textures['b'].loadFromFile("resources/blue.png");
    textures['c'].loadFromFile("resources/cyan.png");
    textures['w'].loadFromFile("resources/white.png");
    textures['a'].loadFromFile("resources/clear.png");

    TextureManager::load("resources/nextPieces.png");
    TextureManager::load("resources/line_clear.png");
}

void Field::initKeys() {
    // Initialize keys:
    for (int i = 0; i < 3; i++)
        keyPressed[i] = 0;
}

void Field::initNextPieceQueue() {
    // Init Next Piece Queue:
    nextQueue.resize(3);    
    for (int i = 0; i < 3; i++) {
        nextQueue[i].setSize(sf::Vector2f(100, 100));
        nextQueue[i].setTexture(TextureManager::get_texture("resources/nextPieces.png"));
        int x;
        switch (rngBag[rngBag.size() - i - 1]) {
            case 0: x = 500;
                    break;
            case 1: x = 400;
                    break;
            case 2: x = 300;
                    break;
            case 3: x = 200;
                    break;
            case 4: x = 600;
                    break;
            case 5: x = 100;
                    break;
            case 6: x = 0;
                    break;
        }
        nextQueue[i].setTextureRect(sf::IntRect(x, 0, 100, 100));
        nextQueue[i].setPosition(sf::Vector2f(570, 100));
    }
    nextQueue[1].move(0, 150);
    nextQueue[2].move(0, 300);
}

void Field::initLineClearAnimations() {
    lineClearAnimate = false;
    for (int i = 0; i < 4; i++) {
        lineClearAnimations[i].setSize(sf::Vector2f(500, 50));
        lineClearAnimations[i].setTexture(TextureManager::get_texture("resources/line_clear.png"));
        lineClearAnimations[i].setTextureRect(noAnimation);
    }
}

void Field::render() {
    for (int i = 0; i < field_width; i++) {
        for (int j = 0; j < field_height; j++) {
            blocks[i][j].render(window);
        }
    }
    for (int i = 0; i < 4; i++) {
        ghostPiece[i].render(window);
    }
    for (int i = 0; i < 3; i++) {
        window->draw(nextQueue[i]);
    }
    for (int i = 0; i < 4; i++) {
        window->draw(lineClearAnimations[i]);
    }
    currentPiece->render(window);
}

void Field::update() {
    updateInput();
    updatePiece();
    updateLineClearAnimations();
    pollClearLines();
}

void Field::updateInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        moveLeft();
        updateGhostPiece();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        moveRight();
        updateGhostPiece();
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
            updateGhostPiece();
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        if (keyPressed[3] == 0) {
            rotate(3);
            updateGhostPiece();
        }
    }
    else {
        keyPressed[2] = 0;
        keyPressed[3] = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (keyPressed[5] == 0) {
            softDropClock.restart();
            keyPressed[5] = 1;
        }
        softDrop();
    }
    else {
        keyPressed[5] = 0;
    }
}

void Field::updatePiece() {
    if (timeStill.getElapsedTime().asMilliseconds() >= 800) {
        this->lockPiece();
    }
    if (rngBag.size() == 0) {
        updateRNG();
        updateQueue();
    }
}

void Field::updateGhostPiece() {
    // Field height = 18 (0 - 17)
    int toFloor = field_height - 1;
    for (int i = 0; i < 4; i++) {
        int yPos = currentPiece->getDefaultPosition(i, 0).y;
        int xPos = currentPiece->getFieldPosition(i, 0).x;
        if (field_height - 1 - yPos < toFloor) {
            toFloor = field_height - 1 - yPos;
        }
    }
    bool temp = false;
    int down = toFloor;
    for (int i = 0; i < 4; i++) {
        int yPos = currentPiece->getDefaultPosition(i, 0).y;
        sf::Vector2i fp  = currentPiece->getFieldPosition(i, 0);
        for (int j = 0; j < field_height; j++) {
            if (blocks[fp.x][j].isSolid()) {
                temp = true;
                if (j - yPos < down) {
                    down = j - yPos;
                }
            }
        }
    }
    if (temp) {
        down--;
    }
    for (int i = 0; i < 4; i++) {
        sf::Vector2i pos = currentPiece->getFieldPosition(i, 0);
        sf::Vector2i pos2 = currentPiece->getDefaultPosition(i, 0);
        ghostPiece[i].set_field_position(sf::Vector2f(
                    pos.x,
                    pos2.y + down
                    )
                );
        ghostPiece[i].set_screen_position(sf::Vector2f(
                    horizontal_offset + 50 * pos.x,
                    vertical_offset + 50 * (pos2.y + down)
                    )
                );
    }
}

void Field::updateRNG() {
    if (rngBag.size() == 0) {
        rngBag = nextBag;
        nextBag.clear();
        srand(time(NULL));
        std::vector<int> temp_bag;
        for (int i = 0; i < 7; i++) {
            temp_bag.push_back(i);
        }

        int tempint;
        while (!temp_bag.empty()) {
            tempint = rand() % temp_bag.size();
            nextBag.push_back(temp_bag[tempint]);
            temp_bag.erase(temp_bag.begin() + tempint);
        }
    }
}

void Field::updateQueue() {
    int nextPiecesInQueue[3];
    int bagSize = rngBag.size();
    if (bagSize > 2) {
        for (int i = 0; i < 3; i++) {
            nextPiecesInQueue[i] = rngBag[rngBag.size() - 1 - i];
        }
    }
    else if (bagSize == 2) {
        nextPiecesInQueue[0] = rngBag[1];
        nextPiecesInQueue[1] = rngBag[0];
        nextPiecesInQueue[2] = nextBag.back();
    }
    else if (bagSize == 1) {
        nextPiecesInQueue[0] = rngBag[0];
        nextPiecesInQueue[1] = nextBag.back();
        nextPiecesInQueue[2] = nextBag[nextBag.size() - 1 - 1];
    }

    for (int i = 0; i < 3; i++) {
        int x;
        switch (nextPiecesInQueue[i]) {
            case 0: x = 500;
                    break;
            case 1: x = 400;
                    break;
            case 2: x = 300;
                    break;
            case 3: x = 200;
                    break;
            case 4: x = 600;
                    break;
            case 5: x = 100;
                    break;
            case 6: x = 0;
                    break;
        }
        nextQueue[i].setTextureRect(sf::IntRect(x, 0, 100, 100));
    }
}

void Field::updateLineClearAnimations() {
    if (lineClearAnimate) {
        for (int i = 0; i < toAnimate; i++) {
            lineClearAnimations[i].setTextureRect(sf::IntRect(noAnimation.left, lineClearAnimations[i].getTextureRect().top + 50, noAnimation.width, noAnimation.height));
            if (lineClearAnimations[i].getTextureRect().top >= noAnimation.top) {
                lineClearAnimate = false;
            }
        }
    }
}

void Field::initRNG() {
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
    for (int i = 0; i < 7; i++) {
        temp_bag.push_back(i);
    }
    while (!temp_bag.empty()) {
        tempint = rand() % temp_bag.size();
        nextBag.push_back(temp_bag[tempint]);
        temp_bag.erase(temp_bag.begin() + tempint);
    }
}

void Field::initGhostPiece() {
    ghostPiece.resize(4);
    for (int i = 0; i < 4; i++) {
        sf::Vector2i pos = currentPiece->getFieldPosition(i, 0);
        ghostPiece[i].setTexture(&textures['a']);
        ghostPiece[i].set_field_position(sf::Vector2f(
                    pos.x, 
                    pos.y
                    )
                );
        ghostPiece[i].set_screen_position(sf::Vector2f(
                    horizontal_offset + 50 * pos.x,
                    vertical_offset + 50 * pos.y
                    )
        );
    }
    updateGhostPiece();
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
        sf::Vector2i fpos = currentPiece->getFieldPosition(i, 0);
        if (fpos.x == 0) {
            return false;
        }
        else if (this->blocks[fpos.x - 1][fpos.y].isSolid()) {
            return false;
        }
    }
    return true;
}

void Field::moveLeft() {   
    
    if (canMoveLeft() && !lineClearAnimate) {
        if (keyPressed[0] == 0) {
            movementDelay.restart();
            currentPiece->moveLeft();
            keyPressed[0] = 1;
        }
        if (keyPressed[0] == 1 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_1) {
            currentPiece->moveLeft();
            keyPressed[0] = 2;
        }
        if (keyPressed[0] == 2 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_2) {
            currentPiece->moveLeft();
            keyPressed[0] = 3;
            movementDelay.restart();
        }
        if (keyPressed[0] == 3 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_3) {
            currentPiece->moveLeft();
            movementDelay.restart();
        }
    }
    
}

bool Field::canMoveRight() {
    for (int i = 0; i < 4; i++) {
        sf::Vector2i fpos = currentPiece->getFieldPosition(i, 0);
        if (fpos.x == field_width - 1) {
            return false;
        }
        else if (this->blocks[fpos.x + 1][fpos.y].isSolid()) {
            return false;
        }
    }
    return true;
}

void Field::moveRight() {

    if (canMoveRight() && !lineClearAnimate) {
        if (keyPressed[1] == 0) {
            movementDelay.restart();
            currentPiece->moveRight();
            keyPressed[1] = 1;
        }
        else if (keyPressed[1] == 1 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_1) {
            currentPiece->moveRight();
            keyPressed[1] = 2;
        }
        else if (keyPressed[1] == 2 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_2) {
            currentPiece->moveRight();
            keyPressed[1] = 3;
            movementDelay.restart();
        }
        else if (keyPressed[1] == 3 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_3) {
            currentPiece->moveRight();
            movementDelay.restart();
        }
    }
}

void Field::moveDown() {
    if (!lineClearAnimate) {
        bool moveDown = true;
        for (int i = 0; i < 4; i++) {
            sf::Vector2i fpos = currentPiece->getFieldPosition(i, 0);
            if (fpos.y == field_height - 1) {
                moveDown = false;
                break;
            }
            else if (this->blocks[fpos.x][fpos.y + 1].isSolid()) {
                moveDown = false;
                break;
            }
        }
        if (moveDown) {
            currentPiece->moveDown();
            timeStill.restart();
        }
    }
}

void Field::hardDrop() {
    if (keyPressed[4] == 0) {
        keyPressed[4] = 1;
        std::set<int> indexes;
        for (int i = 0; i < 4; i++) {
            sf::Vector2i position = currentPiece->getFieldPosition(i, 0);
            int x = position.x;
            int y = position.y;
            while (y < field_height - 1) {
                if (!blocks[x][y + 1].isSolid()) {
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
    if (softDropClock.getElapsedTime().asMilliseconds() > 20) {
        softDropClock.restart();
        moveDown();
    }
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
    rotated_pos[0] = (currentPiece->getFieldPosition(0, r));
    rotated_pos[1] = (currentPiece->getFieldPosition(1, r));
    rotated_pos[2] = (currentPiece->getFieldPosition(2, r));
    rotated_pos[3] = (currentPiece->getFieldPosition(3, r));
    bool valid = true;
    // Case 1: In place
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y >= field_height || rotated_pos[i].x >= field_width || rotated_pos[i].x < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x][rotated_pos[i].y].isSolid()) {
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
        else if (blocks[rotated_pos[i].x][rotated_pos[i].y + 1].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 2;
    valid = true;
    // Case 4: Left
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y >= field_height || rotated_pos[i].x - 1 >= field_width || rotated_pos[i].x - 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y].isSolid()) {
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
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y].isSolid()) {
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
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y + 1].isSolid()) {
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
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y + 1].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 9;
    valid = true;
    // Case 10: Down 2 left
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y + 2 >= field_height || rotated_pos[i].x - 1 >= field_width || rotated_pos[i].x - 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y + 2].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 10;
    valid = true;
    // Case 11: Down 2 Right
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y + 2 >= field_height || rotated_pos[i].x + 1 >= field_width || rotated_pos[i].x + 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y + 2].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 11;
    valid = true;
    // Case 3: Up
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y - 1 >= field_height || rotated_pos[i].x >= field_width || rotated_pos[i].x < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x][rotated_pos[i].y - 1].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 3;
    valid = true;
    // Case 6: Up Left
    for (int i = 0; i < 4; i++) {
        if (rotated_pos[i].y - 1 >= field_height || rotated_pos[i].x - 1 >= field_width || rotated_pos[i].x - 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y - 1].isSolid()) {
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
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y - 1].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) return 7;
    valid = true;
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
        sf::Vector2i fpos = currentPiece->getFieldPosition(i, 0);
        if (fpos.y == field_height - 1) {
            dropDown = false;
            break;
        }
        else if (this->blocks[fpos.x][fpos.y + 1].isSolid()) {
            dropDown = false;
            break;
        }
    }
    if (dropDown) {
        timeStill.restart();
        return;
    }
    for (int i = 0; i < 4; i++) {
        sf::Vector2i fpos = currentPiece->getFieldPosition(i, 0);
        Block* b = currentPiece->getBlock(i);
        this->blocks[fpos.x][fpos.y].setTexture(b->getTexture());
        this->blocks[fpos.x][fpos.y].setSolid();
        linesAffected.insert(fpos.y);
    }
    delete currentPiece;
    if (linesAffected.find(0) != linesAffected.end()) {
        GameOver = true;
    }
    else {
        setClearLines(linesAffected);
    }
}

void Field::setClearLines(std::set<int>& linesAffected) {
    std::set<int> toClear;
    for (auto& line : linesAffected) {
        bool lineCleared = true;
        for (int i = 0; i < field_width; i++) {
            if (!blocks[i][line].isSolid()) {
                lineCleared = false;
                break;
            }
        }
        if (lineCleared) {
            // Remove line from set:
            toClear.insert(line);
        }
    }
    for (int i = 0; i < toClear.size(); i++) {
        lineClearAnimations[i].setTextureRect(animationBegin);
    }
    int j = 0;
    for (auto& line : toClear) {
        lineClearAnimations[j].setPosition(sf::Vector2f(50, 50 + (50 * line)));
        j++;
    }
    generatePiece(rngBag.back());    
    if (toClear.size() > 0) {
        lineClearAnimate = true;
        toAnimate = toClear.size();
        polledLinesForClearing = toClear;
    }
    else {
        rngBag.pop_back();
        timeStill.restart();
        updateGhostPiece();
        updateQueue();
    }
}

void Field::pollClearLines() {
    if (!polledLinesForClearing.empty() && !lineClearAnimate) {
        for (auto& line : polledLinesForClearing) {
            for (int i = line - 1; i >= 0; i--) {
                for (int j = 0; j < field_width; j++) {
                    blocks[j][i + 1].setTexture(blocks[j][i].getTexture());
                    blocks[j][i + 1].setSolid(blocks[j][i].isSolid());
                    blocks[j][i].setTexture(&textures['w']);
                    blocks[j][i].setEmpty();
                }
            }
        }
        switch (polledLinesForClearing.size()) {
            case 1: *Score = *Score + 100;
                    break;
            case 2: *Score = *Score + 300;
                    break;
            case 3: *Score = *Score + 500;
                    break;
            case 4: *Score = *Score + 800;
        }
        *LinesCleared = *LinesCleared + polledLinesForClearing.size();
        this->fScore->setString(std::to_string(*Score));
        this->fLinesCleared->setString(std::to_string(*LinesCleared));
        rngBag.pop_back();
        timeStill.restart();
        updateGhostPiece();
        updateQueue();
        polledLinesForClearing.clear();
    }
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
