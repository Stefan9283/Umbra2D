#include "Scene.h"
#include "Entity.h"

namespace Umbra2D {
        Scene::Scene() {
            auto entity = registry.create();
//            registry.emplace<Umbra2D::Components::Colliders::Circle>(entity, 5);
//            registry.get<Umbra2D::Components::Colliders::Circle>(entity);
        }

    Entity* Scene::addEntity() {
        auto* e = new Entity("", &registry);
        entities.emplace_back(e);
        return e;
    }

    void Scene::gui() {
        if (ImGui::Begin("Scene"))
            for (auto e : entities)
                e->gui();
        ImGui::End();
    }
}
