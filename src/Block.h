#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

const int field_width_v = 10;
const int field_height_v = 18;
//const int vertical_offset = 50;
//const int horizontal_offset = 50;
//const int move_time_1 = 380;
//const int move_time_2 = 450;
//const int move_time_3 = 60;

class Block {
    public:
        // Default Constructor:
        Block();
        ~Block();
        // Display the block to the window:
        void render(sf::RenderWindow* window); 
        // Set Texture of block:
        void setTexture(sf::Texture* texture); // from std::map textures in Field object
        sf::Texture* getTexture();
        // Set Screen Position:
        void set_screen_position(sf::Vector2f pos);
        sf::Vector2f get_screen_position();
        // Set Field Position:
        void set_field_position(sf::Vector2f field_position);
        sf::Vector2f getFieldPosition();
        bool canMoveLeft();
        bool canMoveRight();
        void moveLeft();
        void moveRight();
        bool canMoveDown();
        void moveDown();
        // Move screen_position:
        void move_screen_position(sf::Vector2f offset);
        // Rotation:
        void update_rotation(int current_rotation, int tetramino_size);
        // Is block solid:
        bool isSolid();
        void setSolid();
        void setSolid(bool tf);
        void setEmpty();
    private:
        // Sprite:
        sf::RectangleShape sprite;
        sf::Texture* texture;
        // Coordinate Position on Screen:
        sf::Vector2f screen_position;
        // Field Position:
        sf::Vector2f field_position;
        // Represents a solid block:
        bool solid;
};
