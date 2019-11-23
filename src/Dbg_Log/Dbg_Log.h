#pragma once

#include <iostream>

const bool debugging = true;

class Debug {
    public:
        static const void Log(std::string errormsg);
};
