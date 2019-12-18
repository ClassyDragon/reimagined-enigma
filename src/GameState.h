#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "TextureManager/TextureManager.h"
#include "Sprite/Sprite.h"
#include "Field.h"
#include "precomp.h"

class GameState : public State {
    public:
        // Constructors:
        GameState();
        GameState(sf::RenderWindow* window, int numPieces, int pieceOffset, int* savedScore);

        // Virtual Overrides:
        void update();
        void render();
        int isOver();
        void setWindow(sf::RenderWindow* window);

        // Init Functions:
        void initText();
        void initPauseMenu();

        // Updates:
        void updateScore();
        void updateText();
        void updateInput();

        // Set Which pieces to use
        void setNumPieces(int numPieces);
        void setPieceOffset(int pieceOffset);

    protected:
        // Window Pointer:
        sf::RenderWindow* window;

        // Field of blocks:
        Field field;

        // Background:
        sf::RectangleShape background;
        sf::Texture bg_texture;

        // Score-Related:
        int Score;
        int LinesCleared;
        int Level;
        std::map<std::string, sf::Text> text;
        sf::Font font;

        // Kirb:
        Sprite::anim_sprite kirby;

        // Pointer to high scores:
        int* savedScore;

        // Pause Related:
        int pauseState;
        bool escPressed;
        sf::RectangleShape pauseMenu;
};
