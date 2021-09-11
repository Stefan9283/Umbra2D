#ifndef UMBRA2D_ENGINE_H
#define UMBRA2D_ENGINE_H

#include "Common.h"

namespace Umbra2D {
    class Engine {
    private:
        Umbra2D::Window* w = nullptr;
        Umbra2D::AssetLibrary* lib = nullptr;
    public:
        Engine();
        ~Engine();
        Umbra2D::AssetLibrary* getLibrary();
        Umbra2D::Window* getWindow();
        void loadProject();
        void saveProject();
    };
}

#endif //UMBRA2D_ENGINE_H
