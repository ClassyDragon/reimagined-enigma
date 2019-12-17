#include "Menu.h"

// Default Constructor:
Menu::Menu() {
}

// Constructor:
Menu::Menu(sf::RenderWindow* window) : window(window) {
    isDone = false;
    menuState = 0;
    mouseClicked = false;
    initTextures();
    initBackground();
    initText();
    initButtons();
}

Menu::~Menu() {
    for (auto& b : buttons) {
        delete b;
    }
    buttons.clear();
}

// Virtual Overrides:
void Menu::update() {
    // Update buttons if state has changed:
    if (menuState == MenuState::MARATHON_SELECT || menuState == MenuState::SPRINT_SELECT) {
        for (auto& b : buttons) {
            delete b;
        }
        buttons.clear();
//        menuState = 2;
        buttons.emplace_back(new TetrominoButton(&this->menuState));
        buttons.emplace_back(new PentominoButton(&this->menuState));
        buttons.emplace_back(new BothButton(&this->menuState));
    }
    else if (menuState > 2) {
        for (auto& i : buttons) {
            delete i;
        }
        buttons.clear();
        isDone = menuState;
    }
    // Check buttons:
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    bool isClicked = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
    if (!isClicked) {
        mouseClicked = false;
    }
    else if (isClicked && !mouseClicked) {
        mouseClicked = true;
    }
    else if (isClicked && mouseClicked) {
        isClicked = false;
    }
    for (auto& b : buttons) {
        b->updateState(mousePos, isClicked);
    }
}

void Menu::render() {
    window->draw(background);
    // Render text:
    for (auto& t : text) {
        window->draw(t.second);
    }
    for (auto& b : buttons) {
        b->drawTo(window);
    }
}

int Menu::isOver() {
    return menuState;
}

void Menu::setWindow(sf::RenderWindow* window) {
    this->window = window;
}

// Init Functions:
void Menu::initTextures() {
    TextureManager::load("resources/backgrounds/menuBackground.png");
}

void Menu::initBackground() {
    background.setSize(sf::Vector2f(1200, 1000));
    background.setTexture(TextureManager::get_texture("resources/backgrounds/menuBackground.png"));
}

void Menu::initText() {
    this->font.loadFromFile("resources/Fonts/font.ttf");
    text.insert(std::pair<std::string, sf::Text>("Version No", sf::Text(versionNo, this->font, 30)));
    text.insert(std::pair<std::string, sf::Text>("Credits", sf::Text(credits, this->font, 30)));
    text["Version No"].setPosition(sf::Vector2f(10, 900));
    text["Credits"].setPosition(sf::Vector2f(800, 900));
}

void Menu::initButtons() {
    this->buttons.push_back(new MarathonButton(&this->menuState, window, &font));
    this->buttons.push_back(new SprintButton(&this->menuState, window, &font));
}

// Get Menu State:
int Menu::getMenuState() {
    return this->menuState;
}

void Menu::setMenuState(int state) {
    this->menuState = state;
}


/* MARATHON BUTTON */
// Constructor:
MarathonButton::MarathonButton(int* menuState, sf::RenderWindow* window, sf::Font* font) : menuState(menuState), window(window), font(font) {
    TextureManager::load("resources/Buttons/marathonButton.png");
    TextureManager::load("resources/Buttons/tetrominoButton.png");
    TextureManager::load("resources/Buttons/bothButton.png");
    TextureManager::load("resources/Buttons/pentominoButton.png");
    this->setTexture(TextureManager::get_texture("resources/Buttons/marathonButton.png"));
    this->setNeutralCoordinates(sf::IntRect(0, 0, 175, 50));
    this->setHoveredCoordinates(sf::IntRect(0, 50, 175, 50));
    this->setClickedCoordinates(sf::IntRect(0, 100, 175, 50));
    this->setPosition(sf::Vector2f(475, 632));
    this->description.setFont(*font);
    this->description.setString("Clear 200 lines!");
    this->description.setPosition(sf::Vector2f(665, 640));
    hovered = false;
}

MarathonButton::~MarathonButton() {
}

void MarathonButton::onClick() {
    *menuState = MenuState::MARATHON_SELECT;
}

void MarathonButton::onHover() {
    hovered = true;
}

void MarathonButton::drawTo(sf::RenderWindow* window) {
    if (hovered)
        window->draw(description);
    hovered = false;
    window->draw(this->buttonShape);
}

/* SPRINT BUTTON */
// Constructor:
SprintButton::SprintButton(int* menuState, sf::RenderWindow* window, sf::Font* font) : menuState(menuState), window(window), font(font) {
    TextureManager::load("resources/Buttons/sprintButton.png");
    this->setTexture(TextureManager::get_texture("resources/Buttons/sprintButton.png"));
    this->setNeutralCoordinates(sf::IntRect(0, 0, 175, 50));
    this->setHoveredCoordinates(sf::IntRect(0, 50, 175, 50));
    this->setClickedCoordinates(sf::IntRect(0, 100, 175, 50));
    this->setPosition(sf::Vector2f(475, 702));
    this->description.setFont(*font);
    this->description.setString("Clear 40 lines as quickly as possible!");
    this->description.setPosition(sf::Vector2f(665, 705));
    hovered = false;
}

SprintButton::~SprintButton() {
}

void SprintButton::onClick() {
    *menuState = MenuState::SPRINT_SELECT;
}

void SprintButton::onHover() {
    hovered = true;
}

void SprintButton::drawTo(sf::RenderWindow* window) {
    if (hovered)
        window->draw(description);
    hovered = false;
    window->draw(this->buttonShape);
}

/* Tetraminos */
TetrominoButton::TetrominoButton(int* menuState) : menuState(menuState) {
    this->setTexture(TextureManager::get_texture("resources/Buttons/tetrominoButton.png"));
    this->setNeutralCoordinates(sf::IntRect(0, 0, 175, 50));
    this->setHoveredCoordinates(sf::IntRect(0, 50, 175, 50));
    this->setClickedCoordinates(sf::IntRect(0, 100, 175, 50));
    this->setPosition(sf::Vector2f(475, 632));
}

TetrominoButton::~TetrominoButton() {
}

void TetrominoButton::onClick() {
    switch (*menuState) {
        case MenuState::MARATHON_SELECT: *menuState = MenuState::MARATHON_TETROMINO_ONLY;
                                         break;
        case MenuState::SPRINT_SELECT: *menuState = MenuState::SPRINT_TETROMINO_ONLY;
                                       break;
    }
}

void TetrominoButton::onHover() {
}

/* Pentominoes */
PentominoButton::PentominoButton(int* menuState) : menuState(menuState) {
    this->setTexture(TextureManager::get_texture("resources/Buttons/pentominoButton.png"));
    this->setNeutralCoordinates(sf::IntRect(0, 0, 175, 50));
    this->setHoveredCoordinates(sf::IntRect(0, 50, 175, 50));
    this->setClickedCoordinates(sf::IntRect(0, 100, 175, 50));
    this->setPosition(sf::Vector2f(475, 732));
}

PentominoButton::~PentominoButton() {
}

void PentominoButton::onClick() {
    switch (*menuState) {
        case MenuState::MARATHON_SELECT: *menuState = MenuState::MARATHON_PENTOMINO_ONLY;
                                         break;
        case MenuState::SPRINT_SELECT: *menuState = MenuState::SPRINT_PENTOMINO_ONLY;
                                       break;
    }
}

void PentominoButton::onHover() {
}

/* Both */
BothButton::BothButton(int* menuState) : menuState(menuState) {
    this->setTexture(TextureManager::get_texture("resources/Buttons/bothButton.png"));
    this->setNeutralCoordinates(sf::IntRect(0, 0, 175, 50));
    this->setHoveredCoordinates(sf::IntRect(0, 50, 175, 50));
    this->setClickedCoordinates(sf::IntRect(0, 100, 175, 50));
    this->setPosition(sf::Vector2f(475, 832));
}

BothButton::~BothButton() {
}

void BothButton::onClick() {
    switch (*menuState) {
        case MenuState::MARATHON_SELECT: *menuState = MenuState::MARATHON_BOTH;
                                         break;
        case MenuState::SPRINT_SELECT: *menuState = MenuState::SPRINT_BOTH;
                                       break;
    }
}

void BothButton::onHover() {
}
