#include "Marathon.h"

Marathon::Marathon() {
}

Marathon::Marathon(sf::RenderWindow* window) : window(window), field(window) {
    TextureManager::load("resources/kirby.png");
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

// Init Functions:
void Marathon::initText() {
    if (!this->font.loadFromFile("resources/Fonts/font.ttf")) {
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

// Updates:
void Marathon::update() {
    this->updateDrop();
    this->kirby.update();
    this->field.update();
}

void Marathon::updateDrop() {
    if (drop_delay.getElapsedTime().asMilliseconds() >= dropDelay_ms) {
        field.moveDown();
        drop_delay.restart();
    }
}

void Marathon::render() {
    //window.clear();
    // Render all objects:
    window->draw(background);
    field.render();
    for (auto i : this->text) {
        window->draw(i.second);
    }
    kirby.drawto(window);
}

int Marathon::isOver() {
    return field.isGameOver();
}
