#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Sprite/Sprite.h" // for anim_sprite
#include "TextureManager/TextureManager.h"
#include "State.h"
#include "Marathon.h"
#include "Sprint.h"
#include "Menu.h"

class TetrisGame {
    public:

        // CONSTRUCTORS AND DESTRUCTORS:
        // Default constructor:
        TetrisGame();
        // Constructor with window size:
        TetrisGame(int width, int height, std::string title);

        // Deconstructor:
        ~TetrisGame();

        // Init Functions
        void initTextures();
        void readHighScores();

        // MAIN GAME LOOP:
        void TetrisMain();

        // UPDATE FUNCTIONS:
        void update();
        void updateEvent();
        void updateDrop();

        // RENDER FUNCTIONS:
        void render();

        // Check State:
        void checkState();

    private:
        // Pointer to application window:
        // This pointer will be passed to different objects as a target
        // for rendering.
        sf::RenderWindow window;

        // Window event tracker:
        sf::Event event;

        // Current State:
        std::vector<State*> state;

        // High Score Data:
        std::map<std::string, int> scores;
};
