
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Block {
    public:
        Block();
        ~Block();
        void setTexture(sf::Texture* texture);
    private:
        sf::RectangleShape sprite;
        sf::Texture* texture;
};
