#include "Dbg_Log.h"

void Debug::Log(std::string errormsg) {
    if (debugging)
        std::cout << "Log: " << errormsg << std::endl;
}
