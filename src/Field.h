
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Block.h"

const int field_width = 10;
const int field_height = 20;

class Field {
    public:
        Field(sf::RenderWindow* window);
        ~Field();
        void render();
    private:
        Block* blocks[field_width][field_height];
        std::map<char, sf::Texture*> textures;
        sf::RenderWindow* window;
};
