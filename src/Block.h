
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Block {
    public:
        Block();
        ~Block();
        void setTexture(sf::Texture* texture);
        void render(sf::RenderWindow* window);
        void setPosition(sf::Vector2f pos);
    private:
        sf::RectangleShape sprite;
        sf::Texture* texture;
};
