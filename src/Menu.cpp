#include "Menu.h"

// Default Constructor:
Menu::Menu() {
}

// Constructor:
Menu::Menu(sf::RenderWindow* window) : window(window) {
    isDone = false;
    initTextures();
    initBackground();
    initText();
}

// Virtual Overrides:
void Menu::update() {
    // "Press Enter to Start"
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        isDone = true;
    }
}

void Menu::render() {
    window->draw(background);
    // Render text:
    for (auto& t : text) {
        window->draw(t.second);
    }
}

int Menu::isOver() {
    return (isDone ? 2 : 0);
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
