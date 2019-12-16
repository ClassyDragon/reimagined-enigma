#include "Tetris.h"

// default constructor:
TetrisGame::TetrisGame() {
}

// constructor with window size:
TetrisGame::TetrisGame(int width, int height, std::string title) : menu(&window), marathon(&window, 7, 0) {
    // Initialize Window:
    this->window.create(sf::VideoMode(width, height), title);
    window.setFramerateLimit(30);

    // Initial State:
    state.push_back(&menu);
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
        switch (status) {
            case 3: marathon.setNumPieces(7);
                    marathon.setPieceOffset(0);
                    break;
            case 4: marathon.setNumPieces(15);
                    marathon.setPieceOffset(7);
                    break;
            case 5: marathon.setNumPieces(22);
                    marathon.setPieceOffset(0);
                    break;
        } 
        state.clear();
        state.push_back(&marathon);
    }
}
