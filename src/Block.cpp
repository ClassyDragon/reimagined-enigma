#include "Block.h"

Block::Block() {
    solid = false;
}

Block::~Block() {
}

void Block::render(sf::RenderWindow* window) {
    window->draw(sprite);
}

void Block::setTexture(sf::Texture* texture) {
    this->texture = texture;
    sprite.setTexture(texture);
    sprite.setSize(static_cast<sf::Vector2f>(texture->getSize()));
}

sf::Texture* Block::getTexture() {
    return texture;
}

void Block::setScreenPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void Block::setFieldPosition(sf::Vector2f fieldPosition) {
    this->fieldPosition = fieldPosition;
}

sf::Vector2f Block::getScreenPosition() {
    return screenPosition;
}

sf::Vector2f Block::getFieldPosition() {
    return fieldPosition;
}

bool Block::canMoveLeft() {
    if (fieldPosition.x - 1 < 0)
        return false;
    return true;
}

bool Block::canMoveRight() {
    if (fieldPosition.x + 1 >= field_width_v)
        return false;
    return true;
}

void Block::moveLeft() {
    fieldPosition = sf::Vector2f(fieldPosition.x - 1, fieldPosition.y);
}

void Block::moveRight() {
    fieldPosition = sf::Vector2f(fieldPosition.x + 1, fieldPosition.y);
}

bool Block::canMoveDown() {
    if (fieldPosition.y + 1 >= field_height_v)
        return false;
    return true;
}

void Block::moveDown() {
    fieldPosition = sf::Vector2f(fieldPosition.x, fieldPosition.y + 1);
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
