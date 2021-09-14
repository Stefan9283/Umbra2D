#include "Entity.h"
#include "AssetLibrary.h"
#include "Components/Colliders.h"
#include "Graphics/Shader.h"
#include "Texture.h"
#include "Graphics/Quad.h"
#include "Engines/Engine.h"

extern Umbra2D::Engine* umbra;

long long unsigned int entitiesCount = 0;

namespace Umbra2D {
    Entity::Entity() {
        id = entitiesCount;
        entitiesCount++;
    }
    void Entity::gui() {
//        ImGui::SliderInt(std::string("Pixelation Level ").append(std::to_string(id)).c_str(), (int*)&pixelateLevel, 0, 1000);
//        ImGui::Checkbox(std::string("Draw ").append(std::to_string(id)).c_str(), &render);
//        transform.gui(id);
    }
//    void Entity::setCollider(Colliders::AbstractCollider* c) {
//        delete this->collider;
//        this->collider = c;
//    }
//    Entity::~Entity() {
//        delete this->collider;
//    }
    void Entity::addComponent(Components::Component *c) {
        this->components.emplace_back(c);
    }


}
