#include "Tetris.h"

// default constructor:
TetrisGame::TetrisGame() {
}

// constructor with window size:
TetrisGame::TetrisGame(int width, int height, std::string title) : field(&window) {
    TextureManager::load("resources/kirby.png");
    // Initialize Window:
    this->window.create(sf::VideoMode(width, height), title);
    window.setFramerateLimit(30);

    // Initialize Score
    Score = 0;
    LinesCleared = 0;
    initText();

    // Initialize field:
    field.setScoreRef(&Score);
    field.setLinesClearedRef(&LinesCleared);
    field.setTextRef(&text["vScore"], &text["vLines"]);

    // Initialize Background:
    this->bg_texture.loadFromFile("resources/backgrounds/mario_background.png");
    this->background.setSize(static_cast<sf::Vector2f>(this->bg_texture.getSize()));
    this->background.setTexture(&this->bg_texture);

    // Initial Delay
    this->dropDelay_ms = 350;

    Sprite::Animation a1(0, 2, false);
    std::map<std::string, Sprite::Animation> animations;
    animations.insert(std::pair<std::string, Sprite::Animation>("Idle", a1)); 
    kirby = Sprite::anim_sprite("resources/kirby.png", 200, 200, animations);
    kirby.setPosition(sf::Vector2f(750, 600));
    kirby.set_speed_ms(200);    
}

// default destructor:
TetrisGame::~TetrisGame() {
}

// Init Functions:
void TetrisGame::initText() {
    if (!this->font.loadFromFile("resources/Fonts/font.ttf")) {
        window.close();
        std::cout << "Failed to load font.ttf." << std::endl;
    }
    this->text.insert(std::pair<std::string, sf::Text>("vScore", sf::Text("0", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("vLines", sf::Text("0", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("Lines Cleared", sf::Text("Lines Cleared:", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("Score", sf::Text("Score:", this->font)));
    text["vScore"].setFillColor(sf::Color::White);
    text["vScore"].setPosition(sf::Vector2f(1100, 246));
    text["vLines"].setFillColor(sf::Color::White);
    text["vLines"].setPosition(sf::Vector2f(1100, 300));
    text["Score"].setFillColor(sf::Color::White);
    text["Score"].setPosition(sf::Vector2f(970, 246));
    text["Lines Cleared"].setFillColor(sf::Color::White);
    text["Lines Cleared"].setPosition(sf::Vector2f(850, 300));
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
    this->updateDrop();
    kirby.update();
    field.update();
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

void TetrisGame::updateDrop() {
    if (drop_delay.getElapsedTime().asMilliseconds() >= dropDelay_ms) {
        field.moveDown();
        drop_delay.restart();
        if (field.isGameOver()) {
            window.close();
        }
    }
}

// render all:
void TetrisGame::render() {
    window.clear();
    // Render all objects:
    window.draw(background);
    field.render();
    for (auto i : this->text) {
        window.draw(i.second);
    }
    kirby.drawto(&window);

    // Display the buffer:
    this->window.display();
}
