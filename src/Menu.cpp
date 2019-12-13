#include "Menu.h"

// Constructor:
Menu::Menu(sf::RenderWindow* window) : window(window) {
    isDone = false;
    initTextures();
    initBackground();
}

// Virtual Overrides:
void Menu::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        isDone = true;
    }
}

void Menu::render() {
    window->draw(background);
}

int Menu::isOver() {
    return (isDone ? 2 : 0);
}

// Init Functions:
void Menu::initTextures() {
    TextureManager::load("resources/backgrounds/menuBackground.png");
}

void Menu::initBackground() {
    background.setSize(sf::Vector2f(1200, 1000));
    background.setTexture(TextureManager::get_texture("resources/backgrounds/menuBackground.png"));
}
