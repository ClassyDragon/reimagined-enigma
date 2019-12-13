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
        Marathon();
        Marathon(sf::RenderWindow* window);
        void initText();
        void update();
        void updateDrop();
        void render();
        int isOver();
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
        std::map<std::string, sf::Text> text;
        sf::Font font;

        // Kirb:
        Sprite::anim_sprite kirby;
};
