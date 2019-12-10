#include "Sprite.h"

//==============SPRITE=================//
// Default Constructor:
Sprite::sprite::sprite() {
}

// Constructor with filename:
Sprite::sprite::sprite(std::string filename) {
    this->texture = TextureManager::get_texture(filename);
    this->image.setTexture(this->texture);
    this->image.setSize(static_cast<sf::Vector2f>(texture->getSize()));
}

// Destructor:
Sprite::sprite::~sprite() {
}

void Sprite::sprite::drawto(sf::RenderWindow* window) {
    window->draw(this->image);
}

void Sprite::sprite::setPosition(sf::Vector2f pos) {
    this->image.setPosition(pos);
}

void Sprite::sprite::setScale(sf::Vector2f scale) {
    this->image.setScale(scale);
    float x = scale.x;
    float y = scale.y;
    std::string message = "Scale set to " + std::to_string(x) + " " + std::to_string(y);
    Debug::Log(message);
}

void Sprite::sprite::move(sf::Vector2f offset) {
    this->image.move(offset);
}




//===================ANIM_SPRITE====================//
// Default constructor
Sprite::anim_sprite::anim_sprite() {
}
// Constructor:
Sprite::anim_sprite::anim_sprite(std::string filename, int sprite_width, int sprite_height, std::map<std::string, Sprite::Animation> animations) : sprite(filename) {
    /* Parameters:
     * 1. Filename of Sprite.
     * 2. Width of each sprite.
     * 3. Height of each sprite.
     * 4. Map containing the different animations for a sprite.
     * */
    this->sprite_width = sprite_width;
    this->sprite_height = sprite_height;
    this->animations = animations;

    // Default Initializations:
    this->speed_ms = 50;              // 50ms per frame
    this->begin_delay = speed_ms;     // If delay = speed, there is no delay
    this->end_delay = speed_ms;      
    this->current_animation = "Idle"; // Default Animation is the Idle animation

    // Calculations:
    this->image.setSize(sf::Vector2f(this->sprite_width, this->sprite_height)); // Size of visible sprite
    this->sheet_width = this->texture->getSize().x / sprite_width;              // Number of sprites horizontally
    this->sheet_height = this->texture->getSize().y / sprite_height;            // Number of sprites vertically
    sf::IntRect a(
            sprite_width * (((animations.at(current_animation).get_current_frame() - 1) + animations.at(current_animation).get_start_index()) % sheet_width), // Left
            sprite_height * ((((animations.at(current_animation).get_current_frame() - 1) + animations.at(current_animation).get_start_index()) / sheet_width)), // Top
            sprite_width, // Width
            sprite_height //Height
            ); 
    this->image.setTextureRect(a);
}

// Destructor:
Sprite::anim_sprite::~anim_sprite() {
}

// Set Functions:
void Sprite::anim_sprite::set_speed_ms(int speed_ms) {
    animations.at(current_animation).set_speed_ms(speed_ms);
}

void Sprite::anim_sprite::set_begin_delay_ms(int delay_ms) {
    animations.at(current_animation).set_begin_delay(delay_ms);
}

void Sprite::anim_sprite::set_end_delay_ms(int delay_ms) {
    animations.at(current_animation).set_end_delay(delay_ms);
}

// Update Functions:
void Sprite::anim_sprite::update() {
    this->update_frame();
}

void Sprite::anim_sprite::update_frame() {
    int wait_time;

    // Check delay time:
    if (animations.at(current_animation).beginning_delay()) {
        wait_time = animations.at(current_animation).get_begin_delay();
    }
    else if (animations.at(current_animation).ending_delay()) {
        wait_time = animations.at(current_animation).get_end_delay();
    }
    else {
        wait_time = animations.at(current_animation).get_speed_ms();
    }


    if (this->clock.getElapsedTime().asMilliseconds() >= wait_time) {
        this->advance_frame();
        sf::IntRect a(
                sprite_width * (((animations.at(current_animation).get_current_frame() - 1) + animations.at(current_animation).get_start_index()) % sheet_width), 
                sprite_height * ((((animations.at(current_animation).get_current_frame() - 1) + animations.at(current_animation).get_start_index()) / sheet_width)), 
                sprite_width, 
                sprite_height
                ); 
        this->image.setTextureRect(a);
        this->clock.restart();
    }
}

// Advance Frame:
void Sprite::anim_sprite::advance_frame() {
    this->animations.at(current_animation).advance();
}

// Add a new animation:
void Sprite::anim_sprite::add_animation(std::string name, Sprite::Animation animation) {
    this->animations.insert(std::pair<std::string, Sprite::Animation>(name, animation));
}




//================BACKGROUND==================//
// Constructor:
Sprite::background::background(std::string filename) {
    texture = TextureManager::get_texture(filename);
    image.setSize(static_cast<sf::Vector2f>(this->texture->getSize()));
    image.setTexture(this->texture);
}

// Destructor:
Sprite::background::~background() {
}

// Draw Background to window:
void Sprite::background::drawto(sf::RenderWindow* window) {
    window->draw(this->image);
}
