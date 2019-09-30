
#include "Tetris.h"
#include "Tetramino.h"

// default constructor:
TetrisGame::TetrisGame() {
}

// constructor with window size:
TetrisGame::TetrisGame(int width, int height, std::string title) {
    // Initialize Window:
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

// default destructor:
TetrisGame::~TetrisGame() {
    delete this->window;
}

// main game loop:
void TetrisGame::run() {

    // Update and render the window every frame the window
    // is still open:
    while (this->window->isOpen()) {
        this->update();
        this->render();
    }

}

// update all:
void TetrisGame::update() {
    this->updateEvent();
}

// update window event:
void TetrisGame::updateEvent() {
    // Check the event:
    while (this->window->pollEvent(this->event)) {

        // Check if user has called the window to be closed:
        if (event.type == sf::Event::Closed) {
            // Close the window:
            window->close();
        }

    }
}

// render all:
void TetrisGame::render() {
    // Render all objects:


    // Display the buffer:
    this->window->display();
}
