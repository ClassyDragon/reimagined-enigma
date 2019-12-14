#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "TextureManager/TextureManager.h"
#include "Sprite/Sprite.h"
#include "Field.h"

class Marathon : public State {
    public:
        // Constructors:
        Marathon();
        Marathon(sf::RenderWindow* window);

        // Virtual Overrides:
        void update();
        void render();
        int isOver();
        void setWindow(sf::RenderWindow* window);

        // Init Functions:
        void initText();

        // Updates:
        void updateDrop();

    private:
        // Window Pointer:
        sf::RenderWindow* window;

        // Field of blocks:
        Field field;

        // Background:
        sf::RectangleShape background;
        sf::Texture bg_texture;

        // Clock:
        sf::Clock drop_delay;
        int dropDelay_ms;

        // Score-Related:
        int Score;
        int LinesCleared;
        int Level;
        std::map<std::string, sf::Text> text;
        sf::Font font;

        // Kirb:
        Sprite::anim_sprite kirby;
};
