#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Dbg_Log/Dbg_Log.h"

enum MenuState {
    CLOSE_WINDOW = -1,
    NOSTATE = 0,
    MARATHON_SELECT = 1,
    SPRINT_SELECT = 2,
    MARATHON_TETROMINO_ONLY = 3,
    MARATHON_PENTOMINO_ONLY = 4,
    MARATHON_BOTH = 5,
    SPRINT_TETROMINO_ONLY = 6,
    SPRINT_PENTOMINO_ONLY = 7,
    SPRINT_BOTH = 8,
    RETURN_TO_MENU = 9
};

enum Direction {
    NM = 0,
    Right = 1,
    Left = 2,
    Down = 3,
    Up = 4
};

enum Rotation {
    NR, // No Rotation
    Clockwise,
    Counterclockwise = 3
};

enum Piece {
    /* Tetrominoes */
    S = 0, T, J, L, Z, O, I,
    /* Pentominoes */
    U = 7, M, F, N, P, V, X, W, Y, z, t, l, i, y, s, f, Q, j, n
};

enum Pause {
    NOT_PAUSED = 0,
    IS_PAUSED = 1,
    WAS_PAUSED = 2
};

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
const sf::IntRect IPieceTexture(0, 0, 100, 100);
const sf::IntRect OPieceTexture(100, 0, 100, 100);
const sf::IntRect LPieceTexture(200, 0, 100, 100);
const sf::IntRect JPieceTexture(300, 0, 100, 100);
const sf::IntRect TPieceTexture(400, 0, 100, 100);
const sf::IntRect SPieceTexture(500, 0, 100, 100);
const sf::IntRect ZPieceTexture(600, 0, 100, 100);
const sf::IntRect UPieceTexture(0, 100, 100, 100);
const sf::IntRect MPieceTexture(100, 100, 100, 100);
const sf::IntRect FPieceTexture(200, 100, 100, 100);
const sf::IntRect NPieceTexture(300, 100, 100, 100);
const sf::IntRect PPieceTexture(400, 100, 100, 100);
const sf::IntRect VPieceTexture(500, 100, 100, 100);
const sf::IntRect XPieceTexture(600, 100, 100, 100);
const sf::IntRect YPieceTexture(700, 100, 100, 100);
const sf::IntRect zPieceTexture(800, 100, 100, 100);
const sf::IntRect tPieceTexture(0, 200, 100, 100);
const sf::IntRect lPieceTexture(100, 200, 100, 100);
const sf::IntRect iPieceTexture(200, 200, 100, 100);
const sf::IntRect yPieceTexture(300, 200, 100, 100);
const sf::IntRect sPieceTexture(400, 200, 100, 100);
const sf::IntRect fPieceTexture(500, 200, 100, 100);
const sf::IntRect QPieceTexture(600, 200, 100, 100);
const sf::IntRect jPieceTexture(700, 200, 100, 100);
const sf::IntRect nPieceTexture(800, 200, 100, 100);
const sf::IntRect unknownPieceTexture(800, 0, 100, 100);

// Version Number and Credits:
const std::string versionNo = "Version 1.0";
const std::string credits = "by ClassyDragon\n(github.com/ClassyDragon)";

// Lines needed to finish marathon mode:
const int MARATHON_LIMIT = 200;
const int SPRINT_LIMIT = 40;
