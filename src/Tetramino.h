
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Field.h" // field_width and field_height
#include "Block.h"

class Block;

class Tetramino {
    public:
        // Default Constructor:
        Tetramino();

        // Constructor with type:
        Tetramino(char type, sf::Texture* texture);

        // Default Destructor:
        ~Tetramino();

        // Init functions:
        void initBlockLayout();
        void initBlockPositions(sf::Texture* texture);

        // Render:
        void render(sf::RenderWindow* window);

        // Return character at rotated index:
        char get_block(int x, int y);

        // Rotation functions:
        void rotate_cw(); // Clock-wise
        void rotate_ccw(); // Counter Clock-wise
        void rotate_blocks();

        // Positional functions:
        void move(sf::Vector2f offset);
        void setPosition(sf::Vector2f position);
        bool can_move_left();
        void move_left();
        bool can_move_right();
        void move_right();
        bool can_move_down();
        void move_down();

        // Get Block pointer:
        Block* getBlock(int index);

        // Get Field Position of block
        //int get_field_position(int block, int rotation_offset); // using an integer is confusing, instead use a Vector2f
        sf::Vector2f get_field_position(int block, int rotation_offset);
    protected:
        // Position of individual blocks:
        std::vector<char> init_pos;
        std::vector<int> block_positions;

        // Rotation representation:
        int current_rotation; // Range [0-4]

        // Tetramino Location:
        int vertical_position; // Range [0 - field_height]
        int horizontal_position; // Range [0 - field_width]

        // Graphical Representation:
        std::vector<Block*> blocks; // size 4

        // Tetramino Type:
        char tetramino_type;
};
