
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tetramino.h"
#include "Field.h"
#include "Block.h"

class TetrisGame {
    public:

        // CONSTRUCTORS AND DESTRUCTORS:
        // Default constructor:
        TetrisGame();
        // Constructor with window size:
        TetrisGame(int width, int height, std::string title);
        // Default destructor:
        ~TetrisGame();

        // MAIN GAME LOOP:
        void TetrisMain();

        // UPDATE FUNCTIONS:
        void update();
        void updateEvent();

        // RENDER FUNCTIONS:
        void render();

    private:
        // Pointer to application window:
        // This pointer will be passed to different objects as a target
        // for rendering.
        sf::RenderWindow* window;

        // Window event tracker:
        sf::Event event;

        // Field:
        Field* field;

        // Background:
        sf::RectangleShape* background;
        sf::Texture* bg_texture;
};
