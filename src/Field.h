
#pragma once
#include <iostream>
#include <vector>
#include <set>
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
        void updateInput();
        void updatePiece();
        // Initialize the piece bag with a seed based on the time:
        void init_rng();
        // Generate a piece based on the current bag:
        void generatePiece(int type);
        // Set active window pointer:
        void setWindow(sf::RenderWindow* window);
        // Current Piece functions:
        bool canMoveLeft();
        void moveLeft();
        bool canMoveRight();
        void moveRight();
        void moveDown();
        void hardDrop();
        void softDrop();
        int canRotate(int r);
        void rotate(int r);
        void lockPiece();
        void clearLines(std::set<int>& linesAffected);
        // Game Over Check
        bool isGameOver();

        // Set Score and Line Cleared Ref:
        void setScoreRef(int* Score);
        void setLinesClearedRef(int* LinesCleared);
        void setTextRef(sf::Text* fScore, sf::Text* fLinesCleared);
    private:
        Block* blocks[field_width][field_height];
        std::map<char, sf::Texture> textures;
        sf::RenderWindow* window;
        std::vector<int> rngBag;
        Tetramino* currentPiece;
        sf::Clock* movementDelay;
        int keyPressed[5]; // 0: Not pressed, 1: Pressed shortly, 2: Pressed Long
        sf::Clock timeStill;
        bool GameOver;
        int* Score;
        int* LinesCleared;
        sf::Text* fLinesCleared;
        sf::Text* fScore;
};
