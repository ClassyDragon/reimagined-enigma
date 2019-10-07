
#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Block.h"

const field_width = 10;
const field_height = 20;

class Field {
    public:
        Field();
        ~Field();
    private:
        Block blocks[field_width][field_height];
};
