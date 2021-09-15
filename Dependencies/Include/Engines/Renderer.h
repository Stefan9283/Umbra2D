#ifndef UMBRA2D_RENDERER_H
#define UMBRA2D_RENDERER_H

#include "Common.h"

namespace Umbra2D {
    class Renderer {
        bool render = true;
    public:
        void onUpdate(Scene *scene, Shader* shader);
        bool isActive();
        void toggle();
    };
}

#endif //UMBRA2D_RENDERER_H
