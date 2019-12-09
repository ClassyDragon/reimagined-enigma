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
    sprite.setTexture(this->texture);
    sprite.setSize(static_cast<sf::Vector2f>(texture->getSize()));
}

sf::Texture* Block::getTexture() {
    return this->texture;
}

void Block::set_screen_position(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void Block::set_field_position(sf::Vector2f field_position) {
    this->field_position = field_position;
}

sf::Vector2f Block::get_screen_position() {
    return screen_position;
}

sf::Vector2f Block::get_field_position() {
    return field_position;
}

bool Block::can_move_left() {
    if (field_position.x - 1 < 0)
        return false;
    return true;
}

bool Block::can_move_right() {
    if (field_position.x + 1 >= field_width)
        return false;
    return true;
}

void Block::move_left() {
    field_position = sf::Vector2f(field_position.x - 1, field_position.y);
}

void Block::move_right() {
    field_position = sf::Vector2f(field_position.x + 1, field_position.y);
}

bool Block::can_move_down() {
    if (field_position.y + 1 >= field_height)
        return false;
    return true;
}

void Block::move_down() {
    field_position = sf::Vector2f(field_position.x, field_position.y + 1);
}

void Block::move_screen_position(sf::Vector2f offset) {
    sprite.move(offset);
}

void Block::update_rotation(int current_rotation, int tetramino_size) {
    switch (tetramino_size) {
        case 9: {
                    switch (current_rotation) {
                        case 0: {
                                    break;
                                }
                        case 1: {
                                    break;
                                }
                        case 2: break;
                        case 3: break;
                    }
                }
        case 16: {
                     switch (current_rotation) {
                         case 0: break;
                         case 1: break;
                         case 2: break;
                         case 3: break;
                     }
                 }
    }
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
