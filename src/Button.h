#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
    public:
        // Default Constructor:
        Button();

        // Virtual Destructor:
        virtual ~Button() = 0;

        // Define behaviour after clicking:
        virtual void onClick() = 0;

        // Set texture:
        void setTexture(sf::Texture* texture);

        // Set Position:
        void setPosition(sf::Vector2f position);

        // Unclicked and Unhovered State:
        void setNeutralCoordinates(sf::IntRect neutral);
        
        // Hovered Over State:
        void setHoveredCoordinates(sf::IntRect hovered);

        // Clicked State:
        void setClickedCoordinates(sf::IntRect clicked);

        // Draw:
        void drawTo(sf::RenderWindow* window);

        // Updates:
        void updateState(const sf::Vector2i mousePos, const bool& isClicked);
    private:
        sf::RectangleShape buttonShape;
        sf::IntRect neutral;
        sf::IntRect hovered;
        sf::IntRect clicked;
};
