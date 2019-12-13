#pragma once
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "TextureManager/TextureManager.h"
#include "precomp.h"

class Menu : public State {
    public:
        // Constructor:
        Menu();
        Menu(sf::RenderWindow* window);

        // Virtual Overrides:
        void update();
        void render();
        int isOver();
        void setWindow(sf::RenderWindow* window);

        // Init Functions:
        void initTextures();
        void initBackground();
        void initText();
    private:
        // Background:
        sf::RectangleShape background;

        // Window pointer:
        sf::RenderWindow* window;

        // Determines whether the state is over:
        bool isDone;

        // Version number and credits:
        std::map<std::string, sf::Text> text;
        sf::Font font;
};
