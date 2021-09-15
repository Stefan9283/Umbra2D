#include "Entity.h"

#include <utility>
#include "Engines/Engine.h"
#include "Components/Component.h"
#include "Components/Colliders.h"
#include "Components/Renderable.h"

extern Umbra2D::Umbra2DEngine* umbra;

namespace Umbra2D {
    Entity::Entity(std::string label, entt::registry* reg) {
        this->reg = reg;
        this->id = reg->create();
        this->label = std::move(label);
    }
    uint32_t Entity::getID() {
        return static_cast<std::uint32_t>(id);
    }
    void Entity::gui() { // TODO
        ImGui::Text("%s %d", label.c_str(), getID());
        if (hasComponent<STATIC>())
            getComponent<STATIC>()->gui();
        if (hasComponent<DYNAMIC>())
            getComponent<DYNAMIC>()->gui();

        if (hasComponent<LINE>())
            getComponent<LINE>()->gui();
        if (hasComponent<CIRCLE>())
            getComponent<CIRCLE>()->gui();
        if (hasComponent<RECTANGLE>())
            getComponent<RECTANGLE>()->gui();
    }
    Entity::~Entity() {
        reg->destroy(id);
    }
}

