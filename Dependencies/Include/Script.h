#ifndef UMBRA2D_SCRIPT_H
#define UMBRA2D_SCRIPT_H

#include "Common.h"

// TODO
namespace Umbra2D {
    class Script {
        std::string label = "";
        sol::state lua;
        std::string asText = "";
        std::string path = "";
        bool needsReload = false;
    public:
        Script();
        Script* readFromFile(std::string path);
        void evaluate();
        void gui();
    };
}


#endif //UMBRA2D_SCRIPT_H
