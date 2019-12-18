#include "Block.h"

// Default Constructor:
Block::Block() {
    solid = false;
}

// Draw block to window:
void Block::render(sf::RenderWindow* window) {
    window->draw(sprite);
}

// Set the texture of the block:
void Block::setTexture(sf::Texture* texture) {
    this->texture = texture;
    sprite.setTexture(texture);
    sprite.setSize(static_cast<sf::Vector2f>(texture->getSize()));
}

// Return the address of the block's texture:
sf::Texture* Block::getTexture() {
    return texture;
}

// Set the position of the block on the window:
void Block::setScreenPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

// Set the Vector2i representing the field position:
void Block::setFieldPosition(sf::Vector2i fieldPosition) {
    this->fieldPosition = fieldPosition;
}

// Get the current screen position of the block:
sf::Vector2f Block::getScreenPosition() {
    return screenPosition;
}

// Get the current field position of the block:
sf::Vector2i Block::getFieldPosition() {
    return fieldPosition;
}

void Block::moveLeft() {
    fieldPosition = sf::Vector2i(fieldPosition.x - 1, fieldPosition.y);
}

void Block::moveRight() {
    fieldPosition = sf::Vector2i(fieldPosition.x + 1, fieldPosition.y);
}

void Block::moveDown() {
    fieldPosition = sf::Vector2i(fieldPosition.x, fieldPosition.y + 1);
}

void Block::moveScreenPosition(sf::Vector2f offset) {
    sprite.move(offset);
}

bool Block::isSolid() {
    return solid;
}

void Block::setSolid() {
    solid = true;
}

void Block::setSolid(bool tf) {
    solid = tf;
}

void Block::setEmpty() {
    solid = false;
}
