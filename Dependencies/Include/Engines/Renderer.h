#ifndef UMBRA2D_RENDERER_H
#define UMBRA2D_RENDERER_H

#include "Common.h"

namespace Umbra2D {
    class AbstractRenderer {
        bool render = true;
    public:
        bool isActive();
        void toggle();
        virtual void onUpdate(Scene *scene, Shader* shader) = 0;
    };
    class Renderer : public AbstractRenderer  {
    public:
        void onUpdate(Scene *scene, Shader* shader) override ;
    };

    class CollidersRenderer : public AbstractRenderer {
    public:
        void onUpdate(Scene *scene, Shader* shader) override ;
    };
}

#endif //UMBRA2D_RENDERER_H
