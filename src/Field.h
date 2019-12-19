#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "Tetramino.h"
#include "Block.h"
#include "TextureManager/TextureManager.h"
#include "precomp.h"

const int numKeys = 8;

class Tetramino;

class Field {
    public:
        // Default Constructor:
        Field();

        // Constructor with window pointer:
        Field(sf::RenderWindow* window, int numPieces, int pieceOffset, int* pauseState);

        // Draw Field and Current Piece:
        void render();

        // Initialization:
        void initKeys();
        void initNextPieceQueue();
        void initRNG();
        void initGhostPiece();
        void initLineClearAnimations();
        void initHoldPiece();
        void initMovement();
        void initRotation();
        void initSounds();

        // Updates:
        void update();
        void updateInput();
        void updatePiece();
        void updateGhostPiece();
        void updateRNG();
        void updateQueue();
        void updateLineClearAnimations();
        void updateHoldPiece();
        void pollMovementAndRotation();
        void updateDropDelay();

        // Generate a piece based on a number:
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
        void setClearLines(std::set<int>& linesAffected);
        void pollClearLines();

        // Game Over Check
        int isGameOver();

        // Set Score and Line Cleared Ref:
        void setScoreRef(int* Score);
        void setLinesClearedRef(int* LinesCleared);
        void setLevelRef(int* Level);
        void setTextRef(sf::Text* fScore, sf::Text* fLinesCleared, sf::Text* fLevel);

        // Swap current piece with hold piece:
        void holdCurrentPiece();

        // Poplulate Bag with random numbers:
        void populateBag(std::vector<int>& bag);
        void setNumPieces(int numPieces);
        void setPieceOffset(int pieceOffset);

        // Set win condition lines:
        void setWinLines(int winLines);

        // Pause Game:
        void pause();

        // Unpause Game:
        void unPause();

        // Play random lock noise:
        void playRandomLock();

    private:
        // Field Array:
        Block blocks[field_width][field_height];

        // Pointer to drawing window:
        sf::RenderWindow* window;

        // The Bag TM
        std::vector<int> rngBag;
        std::vector<int> nextBag;
        int numPieces;
        int pieceOffset;

        // Current moveable tetramino
        Tetramino currentPiece;

        // Graphical representation of where the piece will land:
        std::vector<Block> ghostPiece;
        Block clearBlock;

        // Clocks:
        sf::Clock dropDelay;
        int dropTime;
        sf::Clock movementDelay; // For fluid piece movement
        sf::Clock timeStill; // Checks when to lock the piece
        sf::Clock softDropClock; // Determines how quickly the piece falls when holding down

        // States of keys:
        int keyPressed[numKeys]; // 0: Not pressed, 1: Pressed shortly, 2: Pressed Long
        
        // Represents whether the game is over:
        bool GameOver;

        // Reference to Score and Line Cleared counters:
        int* Score;
        int* LinesCleared;
        int* Level;
        sf::Text* fLinesCleared;
        sf::Text* fScore;
        sf::Text* fLevel;

        // Next Piece Queue:
        std::vector<sf::RectangleShape> nextQueue;

        // Hold Piece:
        int holdPiece;
        bool hasPieceBeenSwapped;
        sf::RectangleShape vHoldPiece;

        // Line Clear Animation:
        sf::RectangleShape lineClearAnimations[5];
        bool lineClearAnimate;
        int toAnimate;
        std::set<int> polledLinesForClearing;

        // Polling
        int pMove;
        int pRotate;

        // How many lines cleared to finish:
        int winLines;

        // Pause related:
        int dropTimeRemaining;
        int* pauseState;

        // Sounds:
        std::map<std::string, sf::SoundBuffer> soundBuffers;
        sf::Sound clearSound;
        std::vector<sf::Sound> lockSounds;
};
