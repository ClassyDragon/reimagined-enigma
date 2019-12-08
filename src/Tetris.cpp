#include "Tetris.h"

// default constructor:
TetrisGame::TetrisGame() {
}

// constructor with window size:
TetrisGame::TetrisGame(int width, int height, std::string title) {
    // Initialize Window:
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    // Initialize field:
    this->field = new Field(this->window);

    // Initialize Background:
//    this->bg_texture.loadFromFile("resources/backgrounds/background1.png");
    this->bg_texture.loadFromFile("resources/backgrounds/black_background.png");
    this->background.setSize(static_cast<sf::Vector2f>(this->bg_texture.getSize()));
    this->background.setTexture(&this->bg_texture);

    // Initial Delay
    this->dropDelay_ms = 200;
}

// default destructor:
TetrisGame::~TetrisGame() {
    delete this->window;
}

// main game loop:
void TetrisGame::TetrisMain() {

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
    this->updateDrop();
    field->update();
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

void TetrisGame::updateDrop() {
    if (drop_delay.getElapsedTime().asMilliseconds() >= dropDelay_ms) {
        field->move_down();
        drop_delay.restart();
    }
}

// render all:
void TetrisGame::render() {
    window->clear();
    // Render all objects:
    window->draw(background);
    field->render();

    // Display the buffer:
    this->window->display();
}
