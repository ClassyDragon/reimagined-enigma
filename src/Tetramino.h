
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
        char getBlock(int x, int y);

        // Rotation functions:
        void rotate(int r, int offset); // Clock-wise
        void rotateBlocks(int offset);

        // Positional functions:
        void move(sf::Vector2f offset);
        void setPosition(sf::Vector2f position);
        bool canMoveLeft();
        void moveLeft();
        bool canMoveRight();
        void moveRight();
        bool canMoveDown();
        void moveDown();

        // Get Block pointer:
        Block* getBlock(int index);

        // Get Field Position of block
        //int getFieldPosition(int block, int rotation_offset); // using an integer is confusing, instead use a Vector2f
        sf::Vector2i getFieldPosition(int block, int rotation_offset);
        sf::Vector2i getDefaultPosition(int block, int rotation_offset);

        // Get Num Blocks (Usually 4):
        int getNumBlocks();

        // Get Tetramino type:
        int getType();
    protected:
        // Position of individual blocks:
        std::vector<char> initPos;
        std::vector<int> blockPositions;

        // Rotation representation:
        int currentRotation; // Range [0-4]

        // Tetramino Location:
        int verticalPosition; // Range [0 - field_height]
        int horizontalPosition; // Range [0 - field_width]

        // Graphical Representation:
        std::vector<Block*> blocks; // size 4

        // Tetramino Type:
        char tetraminoType;
        int type;
};
