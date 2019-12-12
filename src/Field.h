
#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Tetramino.h"
#include "Block.h"
#include "TextureManager/TextureManager.h"

const int field_width = 10;
const int field_height = 18;
const int vertical_offset = 50;
const int horizontal_offset = 50;
const int move_time_1 = 380;
const int move_time_2 = 450;
const int move_time_3 = 60;
const sf::IntRect noAnimation(0, 500, 500, 50);
const sf::IntRect animationBegin(0, 0, 500, 50);

class Tetramino;

//class Block;

class Field {
    public:
        // Default Constructor:
        Field();

        // Constructor with window pointer:
        Field(sf::RenderWindow* window);

        // Destructor:
        ~Field();

        // Draw Field and Current Piece:
        void render();

        // Updates:
        void update();
        void updateInput();
        void updatePiece();
        void updateGhostPiece();
        void updateRNG();
        void updateQueue();
        void updateLineClearAnimations();

        // Initialize the piece bag with a seed based on the time:
        void initTextures();
        void initKeys();
        void initNextPieceQueue();
        void initRNG();
        void initGhostPiece();
        void initLineClearAnimations();

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

        // Clear specified lines
        void clearLines(std::set<int>& linesAffected);

        // Game Over Check
        bool isGameOver();

        // Set Score and Line Cleared Ref:
        void setScoreRef(int* Score);
        void setLinesClearedRef(int* LinesCleared);
        void setTextRef(sf::Text* fScore, sf::Text* fLinesCleared);

    private:
        // Field Array:
        Block blocks[field_width][field_height];

        // Block textures:
        std::map<char, sf::Texture> textures;

        // Pointer to drawing window:
        sf::RenderWindow* window;

        // The Bag TM
        std::vector<int> rngBag;
        std::vector<int> nextBag;

        // Current moveable tetramino
        Tetramino* currentPiece;

        // Graphical representation of where the piece will land:
        std::vector<Block> ghostPiece;

        // Clocks:
        sf::Clock movementDelay; // For fluid piece movement
        sf::Clock timeStill; // Checks when to lock the piece
        sf::Clock softDropClock; // Determines how quickly the piece falls when holding down

        // States of keys:
        int keyPressed[6]; // 0: Not pressed, 1: Pressed shortly, 2: Pressed Long
        
        // Represents whether the game is over:
        bool GameOver;

        // Reference to Score and Line Cleared counters:
        int* Score;
        int* LinesCleared;
        sf::Text* fLinesCleared;
        sf::Text* fScore;

        // Next Piece Queue:
        std::vector<sf::RectangleShape> nextQueue;

        // Hold Piece:
        int holdPiece;

        // Line Clear Animation:
        sf::RectangleShape lineClearAnimations[4];
        bool lineClearAnimate;
        int toAnimate;
};
