
#include "Block.h"

Block::Block() {
}

Block::~Block() {
}

void Block::setTexture(sf::Texture* texture) {
    this->texture = texture;
    sprite.setTexture(this->texture);
}
