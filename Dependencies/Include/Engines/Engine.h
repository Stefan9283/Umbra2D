#ifndef UMBRA2D_ENGINE_H
#define UMBRA2D_ENGINE_H

#include <Gui/EngineSettings.h>
#include "Common.h"

namespace Umbra2D {
    class Umbra2DEngine {
    private:
        Umbra2D::Window* w = nullptr;
        Umbra2D::AssetLibrary* lib = nullptr;
        Umbra2D::Gui::EngineSettings* settings;
        Umbra2D::Scene *scene;
    public:
        Umbra2D::Gui::Logger* logger;
        Umbra2D::Graphics::Shader* colliderShader {}; // TODO ????

        Umbra2DEngine();
        ~Umbra2DEngine();
        Umbra2D::AssetLibrary* getLibrary();
        Umbra2D::Window* getWindow();
        void loadProject();
        void saveProject();
        void run();
        glm::vec4 getThemeColor();
    };
}

#endif //UMBRA2D_ENGINE_H
