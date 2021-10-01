#ifndef UMBRA2D_SCENE_H
#define UMBRA2D_SCENE_H

#include "Common.h"

namespace Umbra2D {
        class Scene {
        private:
            std::vector<Entity*> entities;
        public:
            entt::registry registry;

            Scene() = default;
            ~Scene();
            Entity* addEntity(std::string name = "");

            void gui();
        };
}


#endif //UMBRA2D_SCENE_H
