#include "Umbra2D.h"

namespace Umbra2D {
    Entity* Scene::addEntity(std::string name) {
        auto* e = new Entity(name, this);
        entities.emplace_back(e);
        return e;
    }

    void Scene::gui() {
        if (ImGui::Begin("Scene"))
            for (auto e : entities)
                e->gui();
        ImGui::End();
    }

    Scene::~Scene() {
        for (auto& e : entities)
            delete e;
    }
}
