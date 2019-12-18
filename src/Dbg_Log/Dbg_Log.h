#pragma once

#include <iostream>

const bool debugging = true;

class Debug {
    public:
        static void Log(std::string errormsg);
};
