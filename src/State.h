/* ____________ State Class ______________ */
#pragma once
#include <iostream>

class State {
    public:
        State();
        virtual void update() = 0;
        virtual void render() = 0;
        virtual int isOver() = 0;
    protected:
};
