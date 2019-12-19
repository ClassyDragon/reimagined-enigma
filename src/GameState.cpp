#include "GameState.h"

GameState::GameState() {
}

GameState::GameState(sf::RenderWindow* window, int numPieces, int pieceOffset, int* savedScore) : window(window), field(window, numPieces, pieceOffset, &pauseState), savedScore(savedScore) {
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

    // Initialize Background:
    this->bg_texture.loadFromFile("resources/backgrounds/kirby_background.png");
    this->background.setSize(static_cast<sf::Vector2f>(this->bg_texture.getSize()));
    this->background.setTexture(&this->bg_texture);

    Sprite::Animation a1(0, 2, false);
    std::map<std::string, Sprite::Animation> animations;
    animations.insert(std::pair<std::string, Sprite::Animation>("Idle", a1)); 
    kirby = Sprite::anim_sprite("resources/kirby.png", 200, 200, animations);
    kirby.setPosition(sf::Vector2f(750, 600));
    kirby.set_speed_ms(200);    

    pauseState = Pause::NOT_PAUSED;
    escPressed = false;

    initPauseMenu();
}

// Init Functions:
void GameState::initText() {
    if (!this->font.loadFromFile("resources/Fonts/font.ttf")) {
        std::cout << "Failed to load font.ttf." << std::endl;
    }
    this->text.insert(std::pair<std::string, sf::Text>("vScore", sf::Text("0", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("vLines", sf::Text("0", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("Lines Cleared", sf::Text("Lines:", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("Score", sf::Text("Score:", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("Level", sf::Text("Level:", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("vLevel", sf::Text("1", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("High Score", sf::Text("High Score:", this->font)));
    this->text.insert(std::pair<std::string, sf::Text>("vHigh Score", sf::Text("0", this->font)));
    for (auto& t : text) {
        t.second.setFillColor(sf::Color::White);
        t.second.setCharacterSize(45);
        t.second.setOutlineColor(sf::Color::Black);
        t.second.setOutlineThickness(2);
    }
    text["vScore"].setPosition(sf::Vector2f(1050, 246));
    text["vLines"].setPosition(sf::Vector2f(1050, 300));
    text["Score"].setPosition(sf::Vector2f(900, 246));
    text["Lines Cleared"].setPosition(sf::Vector2f(902, 300));
    text["Level"].setPosition(sf::Vector2f(900, 350));
    text["vLevel"].setPosition(sf::Vector2f(1050, 350));
    text["High Score"].setPosition(sf::Vector2f(780, 400));
    text["vHigh Score"].setPosition(sf::Vector2f(1050, 400));

    updateText();
}

void GameState::initPauseMenu() {
    pauseMenu.setSize(sf::Vector2f(989, 799));
    pauseMenu.setTexture(TextureManager::get_texture("resources/paused.png"));
    pauseMenu.setOrigin(sf::Vector2f(989/2, 799/2));
    pauseMenu.setPosition(sf::Vector2f(600, 500));
}

// Updates:
void GameState::update() {
    this->updateScore();
    this->updateText();
    this->updateInput();
    this->kirby.update();
    this->field.update();
}

void GameState::updateScore() {
    if (this->Score > *savedScore) {
        *savedScore = Score;
    }
}

void GameState::updateText() {
    text["vHigh Score"].setString(std::to_string(*savedScore));
}

void GameState::updateInput() {
    // Pause Game:
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        if (!escPressed) {
            switch (pauseState) {
                case 0: this->field.pause();
                        break;
                case 1: this->field.unPause();
                        break;
            }
            escPressed = true;
        }
    }
    else {
        escPressed = false;
    }
}

// Set which pieces to use:
void GameState::setNumPieces(int numPieces) {
    this->field.setNumPieces(numPieces);
}

void GameState::setPieceOffset(int pieceOffset) {
    this->field.setPieceOffset(pieceOffset);
}

void GameState::render() {
    // Render all objects:
    window->draw(background);
    field.render();
    for (auto i : this->text) {
        window->draw(i.second);
    }
    kirby.drawto(window);
    if (pauseState == Pause::IS_PAUSED) {
        window->draw(pauseMenu);
    }
}

int GameState::isOver() {
    return field.isGameOver();
}

void GameState::setWindow(sf::RenderWindow* window) {
    this->window = window;
}
