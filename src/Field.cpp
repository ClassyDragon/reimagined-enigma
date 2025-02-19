#include "Field.h"

// Default Constructor:
Field::Field() {
}

Field::Field(sf::RenderWindow* window, int numPieces, int pieceOffset, int* pauseState) : window(window), numPieces(numPieces), pieceOffset(pieceOffset), pauseState(pauseState) {
    // Set keys as not pressed:
    initKeys();

    // Create empty blocks on field:
    for (int i = 0; i < field_width; i++) {
        for (int j = 0; j < field_height; j++) {
            blocks[i][j] = Block();
            blocks[i][j].setTexture(TextureManager::get_texture("resources/white.png"));
            blocks[i][j].setScreenPosition(sf::Vector2f(horizontal_offset + (50 * i), vertical_offset + (50 * j)));
        }
    }

    // Init Polling:
    initMovement();
    initRotation();

    // Create the initial rng bag:
    initRNG();

    // Generate the first piece:
    generatePiece(rngBag.back());    
    rngBag.pop_back();

    // Create the ghost piece and set its initial position:
    initGhostPiece();

    // Initialize GameOver state:
    GameOver = false;

    // Initialize the next piece queue:
    initNextPieceQueue();

    // Set line clear animation textures and positions:
    initLineClearAnimations();

    // Set hold piece to be empty:
    initHoldPiece();
    updateQueue();

    // Initialize Sounds:
    initSounds();
}

// Draw Field and Current Piece:
void Field::render() {
    // Render blocks in field:
    for (int i = 0; i < field_width; i++) {
        for (int j = 0; j < field_height; j++) {
            blocks[i][j].render(window);
        }
    }
    // Render ghost piece:
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        ghostPiece[i].render(window);
    }
    // Render next piece queue:
    for (int i = 0; i < 3; i++) {
        window->draw(nextQueue[i]);
    }
    // Render line clear animations:
    for (int i = 0; i < 5; i++) {
        window->draw(lineClearAnimations[i]);
    }
    // Render hold piece slot:
    window->draw(vHoldPiece);
    // Render current piece:
    currentPiece.render(window);
}

// Initialization:
void Field::initKeys() {
    // Initialize keys:
    for (int i = 0; i < numKeys; i++)
        keyPressed[i] = 0;
}

void Field::initNextPieceQueue() {
    // Init Next Piece Queue:
    nextQueue.resize(3);    
    for (int i = 0; i < 3; i++) {
        nextQueue[i].setSize(sf::Vector2f(100, 100));
        nextQueue[i].setTexture(TextureManager::get_texture("resources/nextPieces.png"));
        nextQueue[i].setPosition(sf::Vector2f(670, 100));
    }
    // Move the second and third slots down:
    nextQueue[1].move(0, 150);
    nextQueue[2].move(0, 300);
}

void Field::initRNG() {
    rngBag.clear();
    nextBag.clear();
    srand(time(NULL)); // srand with seed based on time
    populateBag(rngBag);
    populateBag(nextBag);
}

void Field::initGhostPiece() {
    clearBlock.setTexture(TextureManager::get_texture("resources/clear.png")); // clearBlock is copied to new instances of ghost piece
    updateGhostPiece();
}

void Field::initLineClearAnimations() {
    lineClearAnimate = false;
    for (int i = 0; i < 5; i++) {
        lineClearAnimations[i].setSize(sf::Vector2f(500, 50));
        lineClearAnimations[i].setTexture(TextureManager::get_texture("resources/line_clear.png"));
        lineClearAnimations[i].setTextureRect(noAnimation);
    }
}

void Field::initHoldPiece() {
    holdPiece = -1;
    vHoldPiece.setSize(sf::Vector2f(100, 100));
    vHoldPiece.setTexture(TextureManager::get_texture("resources/nextPieces.png"));
    vHoldPiece.setTextureRect(sf::IntRect(700, 0, 100, 100));
    vHoldPiece.move(sf::Vector2f(25, 45));
}

void Field::initMovement() {
    // Initialize poll movement to 0:
    pMove = Direction::NM;

    /* KEY:
     * 0 - No movement polled
     * 1 - Move right polled
     * 2 - Move left polled
     */
}

void Field::initRotation() {
    // Initalize poll rotation to 0:
    pRotate = Rotation::NR;

    /* KEY:
     * 0 - No rotation polled
     * 1 - Clockwise Rotation polled
     * 3 - Counterclockwise Rotation polled
     */
}

void Field::initSounds() {
    soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>("Clear", sf::SoundBuffer()));
    soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>("Lock1", sf::SoundBuffer()));
    soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>("Lock2", sf::SoundBuffer()));
    soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>("Lock3", sf::SoundBuffer()));
    soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>("Lock4", sf::SoundBuffer()));
    soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>("Lock5", sf::SoundBuffer()));
    soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>("Lock6", sf::SoundBuffer()));
    soundBuffers.insert(std::pair<std::string, sf::SoundBuffer>("Lock7", sf::SoundBuffer()));
    soundBuffers["Clear"].loadFromFile("resources/Sound/clear.wav");
    soundBuffers["Lock1"].loadFromFile("resources/Sound/lock1.wav");
    soundBuffers["Lock2"].loadFromFile("resources/Sound/lock2.wav");
    soundBuffers["Lock3"].loadFromFile("resources/Sound/lock3.wav");
    soundBuffers["Lock4"].loadFromFile("resources/Sound/lock4.wav");
    soundBuffers["Lock5"].loadFromFile("resources/Sound/lock5.wav");
    soundBuffers["Lock6"].loadFromFile("resources/Sound/lock6.wav");
    soundBuffers["Lock7"].loadFromFile("resources/Sound/lock7.wav");
    lockSounds.resize(7);
    lockSounds[0].setBuffer(soundBuffers["Lock1"]);
    lockSounds[1].setBuffer(soundBuffers["Lock2"]);
    lockSounds[2].setBuffer(soundBuffers["Lock3"]);
    lockSounds[3].setBuffer(soundBuffers["Lock4"]);
    lockSounds[4].setBuffer(soundBuffers["Lock5"]);
    lockSounds[5].setBuffer(soundBuffers["Lock6"]);
    lockSounds[6].setBuffer(soundBuffers["Lock7"]);
    clearSound.setBuffer(soundBuffers["Clear"]);
    clearSound.setVolume(25);
    for (auto& s : lockSounds) {
        s.setVolume(5);
    }
}

// Updates:
void Field::update() {
    updateInput();
    pollMovementAndRotation();
    updateDropDelay();
    updatePiece();
    updateLineClearAnimations();
    pollClearLines();
}

void Field::updateInput() {
    if (*pauseState != Pause::IS_PAUSED) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pMove = Direction::Left;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            pMove = Direction::Right;
        }
        else {
            keyPressed[0] = 0;
            keyPressed[1] = 0;
        }

        // Rotation:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            if (keyPressed[2] == 0) pRotate = Rotation::Clockwise;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            if (keyPressed[3] == 0) pRotate = Rotation::Counterclockwise;
        }
        else {
            keyPressed[2] = 0;
            keyPressed[3] = 0;
        }

        // Vertical Movement:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (keyPressed[5] == 0) {
                softDropClock.restart();
                keyPressed[5] = 1;
            }
            softDrop();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            hardDrop();
        }
        else {
            keyPressed[4] = 0;
            keyPressed[5] = 0;
        }

        // Hold Piece:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            if (keyPressed[6] == 0) {
                holdCurrentPiece();
            }
        }
        else {
            keyPressed[6] = 0;
        }
    }
}

void Field::updatePiece() {
    if (timeStill.getElapsedTime().asMilliseconds() >= 800) {
        this->lockPiece();
    }
    if (rngBag.size() == 0) { // Repopulate bags if empty:
        updateRNG();
        updateQueue();
    }
    // Check if time to drop:
    switch (*pauseState) {
        case Pause::IS_PAUSED: break; // do not drop
        case Pause::WAS_PAUSED: if (dropDelay.getElapsedTime().asMilliseconds() >= dropTimeRemaining) {
                                    moveDown();
                                    *pauseState = Pause::NOT_PAUSED;
                                    dropDelay.restart();
                                }
                               break;
        default: if (dropDelay.getElapsedTime().asMilliseconds() >= dropTime) {
                     moveDown();
                     dropDelay.restart();
                 }
                 break;
    }
}

void Field::updateGhostPiece() {
    // Field height = 18 (0 - 17)
    ghostPiece.clear();
    ghostPiece.resize(currentPiece.getNumBlocks());
    std::set<int> drops;
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        ghostPiece[i] = clearBlock;
        int xPosition = currentPiece.getFieldPosition(i, 0).x;
        int yPosition = currentPiece.getDefaultPosition(i, 0).y;
        int dropDistance = 0;
        while (true) {
            if (dropDistance + 1 >= field_height) {
                dropDistance = dropDistance - yPosition;
                break;
            }
            else if (blocks[xPosition][dropDistance + 1].isSolid()) {
                dropDistance = dropDistance - yPosition;
                break;
            }
            dropDistance++;
        }
        drops.insert(dropDistance);
    }
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        sf::Vector2i fp = currentPiece.getFieldPosition(i, 0);
        sf::Vector2i dp = currentPiece.getDefaultPosition(i, 0);
        ghostPiece[i].setFieldPosition(sf::Vector2i(fp.x, dp.y + *drops.begin()));
        ghostPiece[i].setScreenPosition(sf::Vector2f(horizontal_offset + 50 * fp.x, vertical_offset + 50 * (dp.y + *drops.begin())));
    }
}

void Field::updateRNG() {
    if (rngBag.size() == 0) {
        rngBag = nextBag; // set current bag to bag on standby
        nextBag.clear();
        populateBag(nextBag);
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
        switch (nextPiecesInQueue[i]) {
            case Piece::Z: nextQueue[i].setTextureRect(ZPieceTexture);
                           break;
            case Piece::S: nextQueue[i].setTextureRect(SPieceTexture);
                           break;
            case Piece::L: nextQueue[i].setTextureRect(LPieceTexture);
                           break;
            case Piece::O: nextQueue[i].setTextureRect(OPieceTexture);
                           break;
            case Piece::I: nextQueue[i].setTextureRect(IPieceTexture);
                           break;
            case Piece::T: nextQueue[i].setTextureRect(TPieceTexture);
                           break;
            case Piece::J: nextQueue[i].setTextureRect(JPieceTexture);
                           break;
            case Piece::U: nextQueue[i].setTextureRect(UPieceTexture);
                           break;
            case Piece::M: nextQueue[i].setTextureRect(MPieceTexture);
                           break;
            case Piece::F: nextQueue[i].setTextureRect(FPieceTexture);
                           break;
            case Piece::N: nextQueue[i].setTextureRect(NPieceTexture);
                           break;
            case Piece::P: nextQueue[i].setTextureRect(PPieceTexture);
                           break;
            case Piece::V: nextQueue[i].setTextureRect(VPieceTexture);
                           break;
            case Piece::X: nextQueue[i].setTextureRect(XPieceTexture);
                           break;
            case Piece::Y: nextQueue[i].setTextureRect(YPieceTexture);
                           break;
            case Piece::z: nextQueue[i].setTextureRect(zPieceTexture);
                           break;
            case Piece::t: nextQueue[i].setTextureRect(tPieceTexture);
                           break;
            case Piece::l: nextQueue[i].setTextureRect(lPieceTexture);
                           break;
            case Piece::i: nextQueue[i].setTextureRect(iPieceTexture);
                           break;
            case Piece::y: nextQueue[i].setTextureRect(yPieceTexture);
                           break;
            case Piece::s: nextQueue[i].setTextureRect(sPieceTexture);
                           break;
            case Piece::f: nextQueue[i].setTextureRect(fPieceTexture);
                           break;
            case Piece::Q: nextQueue[i].setTextureRect(QPieceTexture);
                           break;
            case Piece::j: nextQueue[i].setTextureRect(jPieceTexture);
                           break;
            case Piece::n: nextQueue[i].setTextureRect(nPieceTexture);
                           break;
            case -1: break;
            default: nextQueue[i].setTextureRect(unknownPieceTexture);
                     break;
        }
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

void Field::updateHoldPiece() {
    switch (holdPiece) {
        case Piece::Z: vHoldPiece.setTextureRect(ZPieceTexture);
                       break;
        case Piece::S: vHoldPiece.setTextureRect(SPieceTexture);
                       break;
        case Piece::L: vHoldPiece.setTextureRect(LPieceTexture);
                       break;
        case Piece::O: vHoldPiece.setTextureRect(OPieceTexture);
                       break;
        case Piece::I: vHoldPiece.setTextureRect(IPieceTexture);
                       break;
        case Piece::T: vHoldPiece.setTextureRect(TPieceTexture);
                       break;
        case Piece::J: vHoldPiece.setTextureRect(JPieceTexture);
                       break;
        case Piece::U: vHoldPiece.setTextureRect(UPieceTexture);
                       break;
        case Piece::M: vHoldPiece.setTextureRect(MPieceTexture);
                       break;
        case Piece::F: vHoldPiece.setTextureRect(FPieceTexture);
                       break;
        case Piece::N: vHoldPiece.setTextureRect(NPieceTexture);
                       break;
        case Piece::P: vHoldPiece.setTextureRect(PPieceTexture);
                       break;
        case Piece::V: vHoldPiece.setTextureRect(VPieceTexture);
                       break;
        case Piece::X: vHoldPiece.setTextureRect(XPieceTexture);
                       break;
        case Piece::Y: vHoldPiece.setTextureRect(YPieceTexture);
                       break;
        case Piece::z: vHoldPiece.setTextureRect(zPieceTexture);
                       break;
        case Piece::t: vHoldPiece.setTextureRect(tPieceTexture);
                       break;
        case Piece::l: vHoldPiece.setTextureRect(lPieceTexture);
                       break;
        case Piece::i: vHoldPiece.setTextureRect(iPieceTexture);
                       break;
        case Piece::y: vHoldPiece.setTextureRect(yPieceTexture);
                       break;
        case Piece::s: vHoldPiece.setTextureRect(sPieceTexture);
                       break;
        case Piece::f: vHoldPiece.setTextureRect(fPieceTexture);
                       break;
        case Piece::Q: vHoldPiece.setTextureRect(QPieceTexture);
                       break;
        case Piece::j: vHoldPiece.setTextureRect(jPieceTexture);
                       break;
        case Piece::n: vHoldPiece.setTextureRect(nPieceTexture);
                       break;
        case -1: break;
        default: vHoldPiece.setTextureRect(unknownPieceTexture);
                 break;
    }
}

void Field::pollMovementAndRotation() {
    if (pMove != Direction::NM || pRotate != Rotation::NR) {
        if (pMove != Direction::NM && pRotate != Rotation::NR) {
            // Move and rotate simultaneously
            rotate(pRotate);
            pRotate = Rotation::NR;
            if (pMove == Direction::Left) {
                moveLeft();
            }
            else {
                moveRight();
            }
            pMove = Direction::NM;
        }
        else if (pMove != Direction::NM) {
            if (pMove == Direction::Left) {
                moveLeft();
            }
            else {
                moveRight();
            }
            pMove = Direction::NM;
        }
        else if (pRotate != Rotation::NR) {
            rotate(pRotate);
            pRotate = Rotation::NR;
        }
        updateGhostPiece();
    }
}

void Field::updateDropDelay() {
    dropTime = (370 - (*Level * 20));
}

// Generate a piece based on a number:
void Field::generatePiece(int type) {
    switch (type) {
        case Piece::S: currentPiece = Tetramino(Piece::S, TextureManager::get_texture("resources/green.png"));
                break;
        case Piece::T: currentPiece = Tetramino(Piece::T, TextureManager::get_texture("resources/purple.png"));
                break;
        case Piece::J: currentPiece = Tetramino(Piece::J, TextureManager::get_texture("resources/blue.png"));
                break;
        case Piece::L: currentPiece = Tetramino(Piece::L, TextureManager::get_texture("resources/orange.png"));
                break;
        case Piece::Z: currentPiece = Tetramino(Piece::Z, TextureManager::get_texture("resources/red.png"));
                break;
        case Piece::O: currentPiece = Tetramino(Piece::O, TextureManager::get_texture("resources/yellow.png"));
                break;
        case Piece::I: currentPiece = Tetramino(Piece::I, TextureManager::get_texture("resources/cyan.png"));
                break;
        case Piece::U: currentPiece = Tetramino(Piece::U, TextureManager::get_texture("resources/blue.png"));
                break;
        case Piece::M: currentPiece = Tetramino(Piece::M, TextureManager::get_texture("resources/red.png"));
                break;
        case Piece::F: currentPiece = Tetramino(Piece::F, TextureManager::get_texture("resources/blue.png"));
                break;
        case Piece::N: currentPiece = Tetramino(Piece::N, TextureManager::get_texture("resources/red.png"));
                 break;
        case Piece::P: currentPiece = Tetramino(Piece::P, TextureManager::get_texture("resources/yellow.png"));
                 break;
        case Piece::V: currentPiece = Tetramino(Piece::V, TextureManager::get_texture("resources/blue.png"));
                 break;
        case Piece::X: currentPiece = Tetramino(Piece::X, TextureManager::get_texture("resources/purple.png"));
                 break;
        case Piece::Y: currentPiece = Tetramino(Piece::Y, TextureManager::get_texture("resources/cyan.png"));
                 break;
        case Piece::z: currentPiece = Tetramino(Piece::z, TextureManager::get_texture("resources/red.png"));
                 break;
        case Piece::t: currentPiece = Tetramino(Piece::t, TextureManager::get_texture("resources/purple.png"));
                 break;
        case Piece::l: currentPiece = Tetramino(Piece::l, TextureManager::get_texture("resources/green.png"));
                 break;
        case Piece::i: currentPiece = Tetramino(Piece::i, TextureManager::get_texture("resources/cyan.png"));
                 break;
        case Piece::y: currentPiece = Tetramino(Piece::y, TextureManager::get_texture("resources/cyan.png"));
                 break;
        case Piece::s: currentPiece = Tetramino(Piece::s, TextureManager::get_texture("resources/green.png"));
                 break;
        case Piece::f: currentPiece = Tetramino(Piece::f, TextureManager::get_texture("resources/orange.png"));
                 break;
        case Piece::Q: currentPiece = Tetramino(Piece::Q, TextureManager::get_texture("resources/yellow.png"));
                 break;
        case Piece::j: currentPiece = Tetramino(Piece::j, TextureManager::get_texture("resources/blue.png"));
                 break;
        case Piece::n: currentPiece = Tetramino(Piece::n, TextureManager::get_texture("resources/green.png"));
                 break;
        default: currentPiece = Tetramino(Piece::Y, TextureManager::get_texture("resources/red.png"));
                 break;
    }
    //  Verify piece fits on board:
    bool canFit = true;
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        sf::Vector2i dP = currentPiece.getDefaultPosition(i, 0);
        if (blocks[dP.x][dP.y].isSolid()) {
            canFit = false;
            break;
        }
    }
    if (!canFit) {
        GameOver = true;
    }
}

// Set active window pointer:
void Field::setWindow(sf::RenderWindow* window) {
    this->window = window;
}

// Current Piece Functions:
bool Field::canMoveLeft() {
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        sf::Vector2i fpos = currentPiece.getFieldPosition(i, 0);
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
            currentPiece.move(Direction::Left);
            keyPressed[0] = 1;
        }
        else if (keyPressed[0] == 1 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_1) {
            currentPiece.move(Direction::Left);
            keyPressed[0] = 2;
        }
        else if (keyPressed[0] == 2 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_2) {
            currentPiece.move(Direction::Left);
            keyPressed[0] = 3;
            movementDelay.restart();
        }
        else if (keyPressed[0] == 3 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_3) {
            currentPiece.move(Direction::Left);
            movementDelay.restart();
        }
    }
    
}

bool Field::canMoveRight() {
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        sf::Vector2i fpos = currentPiece.getFieldPosition(i, 0);
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
            currentPiece.move(Direction::Right);
            keyPressed[1] = 1;
        }
        else if (keyPressed[1] == 1 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_1) {
            currentPiece.move(Direction::Right);
            keyPressed[1] = 2;
        }
        else if (keyPressed[1] == 2 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_2) {
            currentPiece.move(Direction::Right);
            keyPressed[1] = 3;
            movementDelay.restart();
        }
        else if (keyPressed[1] == 3 && movementDelay.getElapsedTime().asMilliseconds() >= move_time_3) {
            currentPiece.move(Direction::Right);
            movementDelay.restart();
        }
    }
}

void Field::moveDown() {
    if (!lineClearAnimate) {
        bool moveDown = true;
        for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
            sf::Vector2i fpos = currentPiece.getFieldPosition(i, 0);
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
            currentPiece.move(Direction::Down);
            timeStill.restart();
        }
    }
}

void Field::hardDrop() {
    if (keyPressed[4] == 0) {
        keyPressed[4] = 1;
        std::set<int> indexes;
        for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
            sf::Vector2i position = currentPiece.getFieldPosition(i, 0);
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
    std::vector<sf::Vector2i> rotated_pos(currentPiece.getNumBlocks());
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        rotated_pos[i] = currentPiece.getFieldPosition(i, r);
    }
    bool valid = true;
    // Case 1: In place
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
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
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        if (rotated_pos[i].y + 1 >= field_height || rotated_pos[i].x >= field_width || rotated_pos[i].x < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x][rotated_pos[i].y + 1].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 2;
    }
    valid = true;
    // Case 4: Left
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        if (rotated_pos[i].y >= field_height || rotated_pos[i].x - 1 >= field_width || rotated_pos[i].x - 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 4;
    }
    valid = true;
    // Case 5: Right
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        if (rotated_pos[i].y >= field_height || rotated_pos[i].x + 1 >= field_width || rotated_pos[i].x + 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 5;
    }
    valid = true;
    // Case 8: Down Left
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        if (rotated_pos[i].y + 1 >= field_height || rotated_pos[i].x - 1 >= field_width || rotated_pos[i].x - 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y + 1].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 8;
    }
    valid = true;
    // Case 9: Down Right
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        if (rotated_pos[i].y + 1 >= field_height || rotated_pos[i].x + 1 >= field_width || rotated_pos[i].x + 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y + 1].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 9;
    }
    valid = true;
    // Case 10: Down 2 left
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        if (rotated_pos[i].y + 2 >= field_height || rotated_pos[i].x - 1 >= field_width || rotated_pos[i].x - 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y + 2].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 10;
    }
    valid = true;
    // Case 11: Down 2 Right
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        if (rotated_pos[i].y + 2 >= field_height || rotated_pos[i].x + 1 >= field_width || rotated_pos[i].x + 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y + 2].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 11;
    }
    valid = true;
    // Case 3: Up
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        if (rotated_pos[i].y - 1 >= field_height || rotated_pos[i].x >= field_width || rotated_pos[i].x < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x][rotated_pos[i].y - 1].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 3;
    }
    valid = true;
    // Case 6: Up Left
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        if (rotated_pos[i].y - 1 >= field_height || rotated_pos[i].x - 1 >= field_width || rotated_pos[i].x - 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x - 1][rotated_pos[i].y - 1].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 6;
    }
    valid = true;
    // Case 7: Up Right
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        if (rotated_pos[i].y - 1 >= field_height || rotated_pos[i].x + 1 >= field_width || rotated_pos[i].x + 1 < 0) {
            valid = false;
            break;
        }
        else if (blocks[rotated_pos[i].x + 1][rotated_pos[i].y - 1].isSolid()) {
            valid = false;
            break;
        }
    }
    if (valid) {
        return 7;
    }
    valid = true;
    return -1;
}

void Field::rotate(int r) {
    int offset = canRotate(r);
    if (offset != -1 && keyPressed[2] == 0 && keyPressed[3] == 0) {
        keyPressed[2] = 1;
        keyPressed[3] = 1;
        currentPiece.rotate(r, offset);
    }
}

void Field::lockPiece() {
    // Iterate through all blocks in current piece
    // Find the field index that corresponds to that piece's position
    // Transfer the attributes
    std::set<int> linesAffected;
    bool dropDown = true;
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        sf::Vector2i fpos = currentPiece.getFieldPosition(i, 0);
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
    for (int i = 0; i < currentPiece.getNumBlocks(); i++) {
        sf::Vector2i fpos = currentPiece.getFieldPosition(i, 0);
        Block* b = currentPiece.getBlock(i);
        this->blocks[fpos.x][fpos.y].setTexture(b->getTexture());
        this->blocks[fpos.x][fpos.y].setSolid();
        linesAffected.insert(fpos.y);
    }
    if (linesAffected.find(0) != linesAffected.end()) {
        GameOver = true;
        generatePiece(rngBag.back());    
    }
    else {
        setClearLines(linesAffected);
    }
    hasPieceBeenSwapped = false;
}

// Clear specified lines:
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
    for (unsigned i = 0; i < toClear.size(); i++) {
        lineClearAnimations[i].setTextureRect(animationBegin);
    }
    int j = 0;
    for (auto& line : toClear) {
        lineClearAnimations[j].setPosition(sf::Vector2f(150, 50 + (50 * line)));
        j++;
    }
    generatePiece(rngBag.back());    
    rngBag.pop_back();
    if (toClear.size() > 0) {
        clearSound.play();
        lineClearAnimate = true;
        toAnimate = toClear.size();
        polledLinesForClearing = toClear;
    }
    else {
        playRandomLock();
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
                    blocks[j][i].setTexture(TextureManager::get_texture("resources/white.png"));
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
        if (*LinesCleared >= this->winLines) {
            GameOver = true;
        }
        *Level = (*LinesCleared / 10) + 1;
        this->fScore->setString(std::to_string(*Score));
        this->fLinesCleared->setString(std::to_string(*LinesCleared));
        this->fLevel->setString(std::to_string(*Level));
        timeStill.restart();
        updateGhostPiece();
        updateQueue();
        polledLinesForClearing.clear();
    }
}

// Game Over Check:
int Field::isGameOver() {
    return (GameOver ? 9 : 0);
}

// Set Score and Line Cleared Ref:
void Field::setScoreRef(int* Score) {
    this->Score = Score;
}

void Field::setLinesClearedRef(int* LinesCleared) {
    this->LinesCleared = LinesCleared;
}

void Field::setLevelRef(int* Level) {
    this->Level = Level;
    updateDropDelay();
}

void Field::setTextRef(sf::Text* fScore, sf::Text* fLinesCleared, sf::Text* fLevel) {
    this->fScore = fScore;
    this->fLinesCleared = fLinesCleared;
    this->fLevel = fLevel;
}

// Swap current piece with hold piece:
void Field::holdCurrentPiece() {
    keyPressed[6] = 1;
    if (!hasPieceBeenSwapped) {
        hasPieceBeenSwapped = true;
        int temp = currentPiece.getType();
        //delete currentPiece;
        if (holdPiece == -1) {
            generatePiece(rngBag.back());
            rngBag.pop_back();
        }
        else {
            generatePiece(holdPiece);
        }
        holdPiece = temp;
        updateQueue();
        updateGhostPiece();
        updateHoldPiece();
    }
}

// Populate bag with random numbers:
void Field::populateBag(std::vector<int>& bag) {
    std::vector<int> tempBag(numPieces);
    for (int i = 0; i < numPieces; i++) {
        tempBag[i] = i;
    }
    int tempint;
    while (!tempBag.empty()) {
        tempint = rand() % tempBag.size();
        bag.push_back(tempBag[tempint] + pieceOffset);
        tempBag.erase(tempBag.begin() + tempint);
    }
}

void Field::setNumPieces(int numPieces) {
    this->numPieces = numPieces;
}

void Field::setPieceOffset(int pieceOffset) {
    this->pieceOffset = pieceOffset;
    initRNG();
    generatePiece(rngBag.back());
    rngBag.pop_back();
    updateQueue();
    updateGhostPiece();
}

void Field::setWinLines(int winLines) {
    this->winLines = winLines;
}

// Pause Game:
void Field::pause() {
    this->dropTimeRemaining = dropTime - dropDelay.restart().asMilliseconds();
    *pauseState = Pause::IS_PAUSED;
}

// Unpause Game:
void Field::unPause() {
    dropDelay.restart();
    *pauseState = Pause::WAS_PAUSED;
}

// Play random lock noise:
void Field::playRandomLock() {
    int randomNum = rand() % lockSounds.size();
    lockSounds[randomNum].play();
}
