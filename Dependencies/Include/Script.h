#ifndef UMBRA2D_SCRIPT_H
#define UMBRA2D_SCRIPT_H

#include "Common.h"

// TODO
namespace Umbra2D {
    class Script {
        std::string label = "";
        chaiscript::ChaiScript asScript;
        std::string asText = "";
        std::string path = "";
        bool needsReload = false;

        Script* readFromFile(std::string path);
        void evaluate();
        void gui();
    };
}


#endif //UMBRA2D_SCRIPT_H
