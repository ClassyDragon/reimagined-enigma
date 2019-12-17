#include "Button.h"

// Default Constructor:
Button::Button() {
}

// Pure Virtual Destructor:
Button::~Button() {
}

// Set Texture:
void Button::setTexture(sf::Texture* texture) {
    this->buttonShape.setTexture(texture);
}

// Set Position:
void Button::setPosition(sf::Vector2f position) {
    this->buttonShape.setPosition(position);
}

// Set Neutral Coordinates:
void Button::setNeutralCoordinates(sf::IntRect neutral) {
    this->neutral = neutral;
    this->buttonShape.setSize(sf::Vector2f(neutral.width, neutral.height));
    this->buttonShape.setTextureRect(this->neutral);
    this->buttonShape.setPosition(sf::Vector2f(0, 0));
}

// Set Hovered Coordinates:
void Button::setHoveredCoordinates(sf::IntRect hovered) {
    this->hovered = hovered;
}

// Set Click Coordinates:
void Button::setClickedCoordinates(sf::IntRect clicked) {
    this->clicked = clicked;
}

// Draw:
void Button::drawTo(sf::RenderWindow* window) {
    window->draw(this->buttonShape);
}

// Updates:
void Button::updateState(const sf::Vector2i mousePos, const bool& isClicked) {
    if (buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        onHover();
        if (isClicked) {
            buttonShape.setTextureRect(clicked);
            onClick();
            return;
        }
        buttonShape.setTextureRect(hovered);
    }
    else {
        buttonShape.setTextureRect(neutral);
    }
}
