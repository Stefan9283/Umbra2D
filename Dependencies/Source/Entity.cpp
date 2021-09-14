#include "Entity.h"
#include "Engines/Engine.h"

extern Umbra2D::Engine* umbra;

namespace Umbra2D {
    Entity::Entity(entt::registry* reg) {
        this->reg = reg;
        this->id = reg->create();
    }
}
