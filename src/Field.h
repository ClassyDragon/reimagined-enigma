
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
const int move_time_1 = 380;
const int move_time_2 = 450;
const int move_time_3 = 60;

class Tetramino;

class Block;

class Field {
    public:
        // Default Constructor:
        Field();
        // Constructor with window pointer:
        Field(sf::RenderWindow* window);
        ~Field();
        // Draw Field and Current Piece:
        void render();
        // Updates:
        void update();
        void update_input();
        // Initialize the piece bag with a seed based on the time:
        void init_rng();
        // Generate a piece based on the current bag:
        void generate_piece(int type);
        // Set active window pointer:
        void set_window(sf::RenderWindow* window);
        // Current Piece functions:
        bool can_move_left();
        void move_left();
        bool can_move_right();
        void move_right();
        void move_down();
        void hard_drop();
        void soft_drop();
        bool can_rotate_clockwise();
        void rotate_clockwise();
        bool can_rotate_counter_clockwise();
        void rotate_counter_clockwise();
    private:
        Block* blocks[field_width][field_height];
        std::map<char, sf::Texture> textures;
        sf::RenderWindow* window;
        std::vector<int> rng_bag;
        Tetramino* current_piece;
        sf::Clock* movement_delay;
        int key_pressed[4]; // 0: Not pressed, 1: Pressed shortly, 2: Pressed Long
};
