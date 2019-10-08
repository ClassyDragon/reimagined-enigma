
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Block.h"
#include "Tetramino.h"

const int field_width = 10;
const int field_height = 18;
const int vertical_offset = 50;
const int horizontal_offset = 50;

class Tetramino;

class Field {
    public:
        Field(sf::RenderWindow* window);
        ~Field();
        void init_rng();
        void render();
        void generate_piece(int type);
    private:
        Block* blocks[field_width][field_height];
        std::map<char, sf::Texture*> textures;
        sf::RenderWindow* window;
        std::vector<int> rng_bag;
        Tetramino* current_piece;
};
