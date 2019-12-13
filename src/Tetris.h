#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Sprite/Sprite.h" // for anim_sprite
#include "TextureManager/TextureManager.h"
#include "State.h"
#include "Marathon.h"
#include "Menu.h"

class TetrisGame {
    public:

        // CONSTRUCTORS AND DESTRUCTORS:
        // Default constructor:
        TetrisGame();
        // Constructor with window size:
        TetrisGame(int width, int height, std::string title);
        // Default destructor:
        ~TetrisGame();

        // Init Functions
        void initText();

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

        // Field:
//        Field field;

        // Current State:
//        State state;
        std::vector<State*> state;

        // Background:
//        sf::RectangleShape background;
//        sf::Texture bg_texture;

        // Clock
//        sf::Clock drop_delay;
//        int dropDelay_ms;

        // Score-Related
//        int Score;
//        int LinesCleared;
//        std::map<std::string, sf::Text> text;
//        sf::Font font;

        // Kirby
//        Sprite::anim_sprite kirby;
};
