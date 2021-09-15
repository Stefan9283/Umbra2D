#include "Entity.h"
#include "Engines/Engine.h"
#include "Components/Component.h"

extern Umbra2D::Engine* umbra;

namespace Umbra2D {
    Entity::Entity(entt::registry* reg) {
        this->reg = reg;
        this->id = reg->create();
    }
    uint32_t Entity::getID() {
        return (uint32_t)id;
    }
    void Entity::gui() { // TODO
//        if (hasComponent<CIRCLE>())
//            std::cout << "YESSSS\n";
//        else std::cout << "NO\n";
    }

    Entity::~Entity() {
        reg->destroy(id);
    }
}
