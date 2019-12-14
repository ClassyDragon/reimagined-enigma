#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Dbg_Log/Dbg_Log.h"

// Global Variables:

const int field_width = 10;
const int field_height = 18;
const int vertical_offset = 50;
const int horizontal_offset = 150;
const int move_time_1 = 125;
const int move_time_2 = 50;
const int move_time_3 = 50;
const sf::IntRect noAnimation(0, 500, 500, 50);
const sf::IntRect animationBegin(0, 0, 500, 50);

// Next Piece and Hold Piece Texture Positions:
const sf::IntRect iPieceTexture(0, 0, 100, 100);
const sf::IntRect oPieceTexture(100, 0, 100, 100);
const sf::IntRect lPieceTexture(200, 0, 100, 100);
const sf::IntRect jPieceTexture(300, 0, 100, 100);
const sf::IntRect tPieceTexture(400, 0, 100, 100);
const sf::IntRect sPieceTexture(500, 0, 100, 100);
const sf::IntRect zPieceTexture(600, 0, 100, 100);

// Version Number and Credits:
const std::string versionNo = "Version 1.0.2b";
const std::string credits = "by ClassyDragon\n(github.com/ClassyDragon)";

// Lines needed to finish marathon mode:
const int MARATHON_LIMIT = 200;
