#ifndef UMBRA2D_SCENE_H
#define UMBRA2D_SCENE_H

#include "Common.h"
#include "Entity.h"

namespace Umbra2D {
        class Scene {
        private:
            std::vector<Entity*> entities;
        public:
            entt::registry registry;

            Scene();
            Entity* addEntity();

            void gui();
        };
}


#endif //UMBRA2D_SCENE_H
