
#include "Block.h"

Block::Block() {
}

Block::~Block() {
}

void Block::render(sf::RenderWindow* window) {
    window->draw(sprite);
}

void Block::setTexture(sf::Texture* texture) {
    this->texture = texture;
    sprite.setTexture(this->texture);
    sprite.setSize(static_cast<sf::Vector2f>(texture->getSize()));
}

void Block::set_screen_position(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void Block::set_field_position(sf::Vector2f field_position) {
    this->field_position = field_position;
}

void Block::move_screen_position(sf::Vector2f offset) {
    sprite.move(offset);
}
