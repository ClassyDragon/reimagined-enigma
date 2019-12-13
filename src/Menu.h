#pragma once
#include <SFML/Graphics.hpp>
#include "State.h"
#include "TextureManager/TextureManager.h"

class Menu : public State {
    public:
        // Constructor:
        Menu(sf::RenderWindow* window);

        // Virtual Overrides:
        void update();
        void render();
        int isOver();

        // Init Functions:
        void initTextures();
        void initBackground();
    private:
        sf::RectangleShape background;
        sf::RenderWindow* window;
        bool isDone;
};
