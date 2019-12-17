#include "Sprint.h"

Sprint::Sprint() {
}

Sprint::Sprint(sf::RenderWindow* window, int numPieces, int pieceOffset) : window(window), field(window, numPieces, pieceOffset) {
    // Initialize Score
    Score = 0;
    LinesCleared = 0;
    Level = 1;
    initText();

    // Initialize field:
    field.setScoreRef(&Score);
    field.setLinesClearedRef(&LinesCleared);
    field.setLevelRef(&Level);
    field.setTextRef(&text["vScore"], &text["vLines"], &text["vLevel"]);
    field.setWinLines(40);

    // Initialize Background:
    this->bg_texture.loadFromFile("resources/backgrounds/kirby_background.png");
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
void Sprint::initText() {
    if (!this->font.loadFromFile("resources/Fonts/font.ttf")) {
        std::cout << "Failed to load font.ttf." << std::endl;
    }
    this->text.insert(std::pair<std::string, sf::Text>("vScore", sf::Text("0", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("vLines", sf::Text("0", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("Lines Cleared", sf::Text("Lines:", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("Score", sf::Text("Score:", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("Level", sf::Text("Level:", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("vLevel", sf::Text("1", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("Clock", sf::Text("00:00:00", this->font)));
    for (auto& t : text) {
        t.second.setFillColor(sf::Color::White);
        t.second.setCharacterSize(45);
        t.second.setOutlineColor(sf::Color::Black);
        t.second.setOutlineThickness(2);
    }
    text["vScore"].setPosition(sf::Vector2f(1100, 246));
    text["vLines"].setPosition(sf::Vector2f(1100, 300));
    text["Score"].setPosition(sf::Vector2f(920, 246));
    text["Lines Cleared"].setPosition(sf::Vector2f(922, 300));
    text["Level"].setPosition(sf::Vector2f(920, 350));
    text["vLevel"].setPosition(sf::Vector2f(1100, 350));
    text["Clock"].setPosition(sf::Vector2f(950, 400));
}

// Updates:
void Sprint::update() {
    this->updateDrop();
    //this->updateClock();
    this->kirby.update();
    this->field.update();
}

void Sprint::updateDrop() {
    if (drop_delay.getElapsedTime().asMilliseconds() >= dropDelay_ms) {
        field.moveDown();
        drop_delay.restart();
    }
    // Update drop delay time:
    dropDelay_ms = (370 - (Level * 20));
}

void Sprint::updateClock() {
    std::string formattedTime = "";
    //formatString(formattedTime);
    //text["Clock"].setString(formattedTime);
}

void Sprint::setNumPieces(int numPieces) {
    this->field.setNumPieces(numPieces);
}

void Sprint::setPieceOffset(int pieceOffset) {
    this->field.setPieceOffset(pieceOffset);
}

void Sprint::formatString(std::string& formattedString) {
    std::stringstream ss;
    sf::Time currentTime = playTime.getElapsedTime();
    int minutes = static_cast<int>(currentTime.asSeconds()) / 60;
    int seconds = static_cast<int>(currentTime.asSeconds()) % 60;
    int milli = currentTime.asMilliseconds() % 1000;
    ss << std::setfill('0') << std::setw(2);
//    formattedString = std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(milli);
    ss << minutes << ":" << std::setw(2) << seconds << ":" << std::setw(2) << milli;
    ss >> formattedString;
}

void Sprint::render() {
    // Render all objects:
    window->draw(background);
    field.render();
    for (auto i : this->text) {
        window->draw(i.second);
    }
    kirby.drawto(window);
}

int Sprint::isOver() {
    return field.isGameOver();
}

void Sprint::setWindow(sf::RenderWindow* window) {
    this->window = window;
}
