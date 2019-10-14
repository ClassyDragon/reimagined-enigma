
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Block {
    public:
        // Default Constructor:
        Block();
        ~Block();
        // Display the block to the window:
        void render(sf::RenderWindow* window); 
        // Set Texture of block:
        void setTexture(sf::Texture* texture); // from std::map textures in Field object
        // Set Screen Position:
        void set_screen_position(sf::Vector2f pos);
        // Set Field Position:
        void set_field_position(sf::Vector2f field_position);
        // Move screen_position:
        void move_screen_position(sf::Vector2f offset);
    private:
        // Sprite:
        sf::RectangleShape sprite;
        sf::Texture* texture;
        // Coordinate Position on Screen:
        sf::Vector2f screen_position;
        // Field Position:
        sf::Vector2f field_position;
};
