#ifndef UMBRA2D_SCENE_H
#define UMBRA2D_SCENE_H

#include "Common.h"

namespace Umbra2D {
        class Scene {
        private:
            entt::registry registry;
//            std::vector<Entity> entities;
        public:
            Scene();
        };
}


#endif //UMBRA2D_SCENE_H
