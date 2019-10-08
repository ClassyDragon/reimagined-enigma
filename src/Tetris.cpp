
#include "Tetris.h"

// default constructor:
TetrisGame::TetrisGame() {
}

// constructor with window size:
TetrisGame::TetrisGame(int width, int height, std::string title) {
    // Initialize Window:
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), title);

    // Initialize field:
    this->field = new Field(window);

    // Initialize Background:
    this->bg_texture = new sf::Texture;
    this->background = new sf::RectangleShape;
    this->bg_texture->loadFromFile("resources/backgrounds/background1.png");
    this->background->setSize(static_cast<sf::Vector2f>(this->bg_texture->getSize()));
//    this->background->setSize(sf::Vector2f(1600, 1200));
    this->background->setTexture(this->bg_texture);
}

// default destructor:
TetrisGame::~TetrisGame() {
    delete this->window;
    delete this->field;
    delete this->bg_texture;
    delete this->background;
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
    window->clear();
    // Render all objects:
    window->draw(*background);
    field->render();

    // Display the buffer:
    this->window->display();
}
