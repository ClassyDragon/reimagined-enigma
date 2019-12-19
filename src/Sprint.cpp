#include "Sprint.h"

Sprint::Sprint() {
}

Sprint::Sprint(sf::RenderWindow* window, int numPieces, int pieceOffset, int* savedScore) : GameState(window, numPieces, pieceOffset, savedScore) {
    field.setWinLines(40);
}

// Updates:
void Sprint::updateClock() {
    std::string formattedTime = "";
    //formatString(formattedTime);
    //text["Clock"].setString(formattedTime);
}

void Sprint::formatString(std::string& formattedString) {
    std::stringstream ss;
    sf::Time currentTime = playTime.getElapsedTime();
    int minutes = static_cast<int>(currentTime.asSeconds()) / 60;
    int seconds = static_cast<int>(currentTime.asSeconds()) % 60;
    int milli = currentTime.asMilliseconds() % 1000;
    ss << std::setfill('0') << std::setw(2);
//    formattedString = std::to_string(minutes) + ":" + std::to_string(seconds) + ":" + std::to_string(milli);
    ss << minutes << ":" << std::setw(2) << seconds << ":" << std::setw(2) << milli;
    ss >> formattedString;
}
