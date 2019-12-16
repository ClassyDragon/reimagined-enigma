#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Button.h"
#include "TextureManager/TextureManager.h"
#include "precomp.h"

class Menu : public State {
    public:
        // Constructor:
        Menu();
        Menu(sf::RenderWindow* window);
        ~Menu();

        // Virtual Overrides:
        void update();
        void render();
        int isOver();
        void setWindow(sf::RenderWindow* window);

        // Init Functions:
        void initTextures();
        void initBackground();
        void initText();
        void initButtons();

        // Get Menu State:
        int getMenuState();
    private:
        // Background:
        sf::RectangleShape background;

        // Window pointer:
        sf::RenderWindow* window;

        // Determines whether the state is over:
        bool isDone;
        int menuState;

        // Version number and credits:
        std::map<std::string, sf::Text> text;
        sf::Font font;

        // Buttons:
        std::vector<Button*> buttons;

        bool mouseClicked;
};

class MarathonButton : public Button {
    public:
        // Constructor:
        MarathonButton(int* menuState);

        // Destructor:
        ~MarathonButton();

        // OnClick:
        void onClick();

    private:
        int* menuState;
};

class TetrominoButton : public Button {
    public:
        // Constructor:
        TetrominoButton(int* menuState);

        // Destructor:
        ~TetrominoButton();

        // OnClick:
        void onClick();

    private:
        int* menuState;
};

class PentominoButton : public Button {
    public:
        // Constructor:
        PentominoButton(int* menuState);

        // Destructor:
        ~PentominoButton();

        // OnClick:
        void onClick();

    private:
        int* menuState;
};

class BothButton : public Button {
    public:
        // Constructor:
        BothButton(int* menuState);

        // Destructor:
        ~BothButton();

        // OnClick:
        void onClick();

    private:
        int* menuState;
};
