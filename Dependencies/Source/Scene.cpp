#include "Scene.h"


namespace Umbra2D {
        Scene::Scene() {
            auto entity = registry.create();
//            registry.emplace<Umbra2D::Components::Colliders::Circle>(entity, 5);
//            registry.get<Umbra2D::Components::Colliders::Circle>(entity);
        }
}
