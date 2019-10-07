
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Tetramino {
    public:
        // Default Constructor:
//        Tetramino();

        // Constructor with type:
        Tetramino(char type);

        // Default Destructor:
        ~Tetramino();

        // Return character at rotated index:
        char get_block(int x, int y);

        // Rotation functions:
        void rotate_cw(); // Clock-wise
        void rotate_ccw(); // Counter Clock-wise
    protected:
        std::vector<char> init_pos;
        int current_rotation;
};
