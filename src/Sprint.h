#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "State.h"
#include "TextureManager/TextureManager.h"
#include "Sprite/Sprite.h"
#include "Field.h"

class Sprint : public GameState {
    public:
        // Constructors:
        Sprint();
        Sprint(sf::RenderWindow* window, int numPieces, int pieceOffset, int* savedScore);

        // Updates:
        void updateClock();

        // Format String based on clock time:
        void formatString(std::string& formattedString);

    private:
        // Clock:
        sf::Clock playTime;
};
