#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "State.h"
#include "TextureManager/TextureManager.h"
#include "Sprite/Sprite.h"
#include "Field.h"

class Marathon : public GameState {
    public:
        // Constructors:
        Marathon();
        Marathon(sf::RenderWindow* window, int numPieces, int pieceOffset, int* savedScore);

    private:
};
