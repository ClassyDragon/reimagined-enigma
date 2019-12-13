/* ____________ State Class ______________ */
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class State {
    public:
        State();
        virtual void update() = 0;
        virtual void render() = 0;
        virtual int isOver() = 0;
        virtual void setWindow(sf::RenderWindow* window) = 0;
    protected:
};
