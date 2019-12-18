#include "Tetris.h"

// default constructor:
TetrisGame::TetrisGame() {
}

// constructor with window size:
//TetrisGame::TetrisGame(int width, int height, std::string title) : menu(&window), marathon(&window, 7, 0), sprint(&window, 7, 0) {
TetrisGame::TetrisGame(int width, int height, std::string title) {
    // Initialize Window:
    this->window.create(sf::VideoMode(width, height), title);
    window.setFramerateLimit(30);

    initTextures();
    readHighScores();

    // Initial State:
    state.push_back(new Menu(&window));
}

// Init Functions:
void TetrisGame::initTextures() {
    // Every texture the game uses:
    TextureManager::load("resources/backgrounds/menuBackground.png");
    TextureManager::load("resources/Buttons/marathonButton.png");
    TextureManager::load("resources/Buttons/tetrominoButton.png");
    TextureManager::load("resources/Buttons/bothButton.png");
    TextureManager::load("resources/Buttons/pentominoButton.png");
    TextureManager::load("resources/Buttons/sprintButton.png");
    TextureManager::load("resources/kirby.png");
    TextureManager::load("resources/red.png");
    TextureManager::load("resources/purple.png");
    TextureManager::load("resources/yellow.png");
    TextureManager::load("resources/green.png");
    TextureManager::load("resources/orange.png");
    TextureManager::load("resources/blue.png");
    TextureManager::load("resources/cyan.png");
    TextureManager::load("resources/white.png");
    TextureManager::load("resources/clear.png");
    TextureManager::load("resources/nextPieces.png");
    TextureManager::load("resources/line_clear.png");
    TextureManager::load("resources/paused.png");
}

void TetrisGame::readHighScores() {
    std::ifstream ifs("save/highscores.txt", std::ifstream::in);
    std::string currentLine;
    int score;
    while (ifs >> currentLine) {
        if (currentLine == "MARATHON_TETROMINO_ONLY:") {
            ifs >> score;
            if (ifs.bad()) {
                ifs.clear();
                score = 0;
            }
            scores["MARATHON_TETROMINO_ONLY"] = score;
        }
        else if (currentLine == "MARATHON_PENTOMINO_ONLY:") {
            ifs >> score;
            if (ifs.bad()) {
                ifs.clear();
                score = 0;
            }
            scores["MARATHON_PENTOMINO_ONLY"] = score;
        }
        else if (currentLine == "MARATHON_BOTH:") {
            ifs >> score;
            if (ifs.bad()) {
                ifs.clear();
                score = 0;
            }
            scores["MARATHON_BOTH"] = score;
        }
        else if (currentLine == "SPRINT_TETROMINO_ONLY:") {
            ifs >> score;
            if (ifs.bad()) {
                ifs.clear();
                score = 0;
            }
            scores["SPRINT_TETROMINO_ONLY"] = score;
        }
        else if (currentLine == "SPRINT_PENTOMINO_ONLY:") {
            ifs >> score;
            if (ifs.bad()) {
                ifs.clear();
                score = 0;
            }
            scores["SPRINT_PENTOMINO_ONLY"] = score;
        }
        else if (currentLine == "SPRINT_BOTH:") {
            ifs >> score;
            if (ifs.bad()) {
                ifs.clear();
                score = 0;
            }
            scores["SPRINT_BOTH"] = score;
        }
        else { //if (currentLine.length() >= 2) {
            ifs.ignore(256, '\n');
        }
    }
}

// main game loop:
void TetrisGame::TetrisMain() {
    // Update and render the window every frame the window
    // is still open:
    while (this->window.isOpen()) {
        this->update();
        this->render();
    }

}

// Deconstructor:
TetrisGame::~TetrisGame() {
    // Write the high scores back to the file:
    std::ofstream ofst("save/highscores.txt", std::ofstream::out|std::ofstream::trunc); 
    ofst << "// Marathon Mode High Scores:" << std::endl;
    ofst << "MARATHON_TETROMINO_ONLY: " << scores["MARATHON_TETROMINO_ONLY"] << std::endl;
    ofst << "MARATHON_PENTOMINO_ONLY: " << scores["MARATHON_PENTOMINO_ONLY"] << std::endl;
    ofst << "MARATHON_BOTH: " << scores["MARATHON_BOTH"] << std::endl << std::endl;
    ofst << "// Sprint Mode High Scores:" << std::endl;
    ofst << "SPRINT_TETROMINO_ONLY: " << scores["SPRINT_TETROMINO_ONLY"] << std::endl;
    ofst << "SPRINT_PENTOMINO_ONLY: " << scores["SPRINT_PENTOMINO_ONLY"] << std::endl;
    ofst << "SPRINT_BOTH: " << scores["SPRINT_BOTH"] << std::endl;
    ofst.close();
    for (auto& s : state) {
        delete s;
    }
    state.clear();
}

// update all:
void TetrisGame::update() {
    this->updateEvent();
    state.front()->update();
    this->checkState();
}

// update window event:
void TetrisGame::updateEvent() {
    // Check the event:
    while (this->window.pollEvent(this->event)) {
        // Check if user has called the window to be closed:
        if (event.type == sf::Event::Closed) {
            // Close the window:
            window.close();
        }

    }
}

// render all:
void TetrisGame::render() {
    window.clear();
    // Render all objects:
    this->state.front()->render();
    // Display the buffer:
    this->window.display();
}

// Check State:
void TetrisGame::checkState() {
    int status = state.front()->isOver();
    if (status == -1) {
        window.close();
    }
    else if (status > 2) {
        for (auto& i : state)
            delete i;
        switch (status) {
            case MenuState::MARATHON_TETROMINO_ONLY: state.clear();
                                                     state.push_back(new Marathon(&window, 7, 0, &scores["MARATHON_TETROMINO_ONLY"]));
                                                     break;
            case MenuState::MARATHON_PENTOMINO_ONLY: state.clear();
                                                     state.push_back(new Marathon(&window, 18, 7, &scores["MARATHON_PENTOMINO_ONLY"]));
                                                     break;
            case MenuState::MARATHON_BOTH: state.clear();
                                           state.push_back(new Marathon(&window, 25, 0, &scores["MARATHON_BOTH"]));
                                           break;
            case MenuState::SPRINT_TETROMINO_ONLY: state.clear();
                                                   state.push_back(new Sprint(&window, 7, 0, &scores["SPRINT_TETROMINO_ONLY"]));
                                                   break;
            case MenuState::SPRINT_PENTOMINO_ONLY: state.clear();
                                                   state.push_back(new Sprint(&window, 18, 7, &scores["SPRINT_PENTOMINO_ONLY"]));
                                                   break;
            case MenuState::SPRINT_BOTH: state.clear();
                                         state.push_back(new Sprint(&window, 25, 0, &scores["SPRINT_BOTH"]));
                                         break;
            case MenuState::RETURN_TO_MENU: state.clear();
                                            state.push_back(new Menu(&window));
                                            break;
        } 
    }
}
