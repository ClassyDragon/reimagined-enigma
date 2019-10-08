
#include "Block.h"

Block::Block() {
}

Block::~Block() {
}

void Block::setTexture(sf::Texture* texture) {
    this->texture = texture;
    sprite.setTexture(this->texture);
    sprite.setSize(static_cast<sf::Vector2f>(texture->getSize()));
}

void Block::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void Block::render(sf::RenderWindow* window) {
    window->draw(sprite);
}
