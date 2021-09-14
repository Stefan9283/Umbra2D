#include "Entity.h"
#include "AssetLibrary.h"
#include "Components/Colliders.h"
#include "Graphics/Shader.h"
#include "Graphics/Quad.h"
#include "Texture.h"
#include "Engines/Engine.h"

extern Umbra2D::Engine* umbra;

namespace Umbra2D {
    Entity::Entity(entt::registry* reg) {
        this->reg = reg;
        this->id = reg->create();
    }

    template<typename T, typename... Args>
    void Entity::addComponent(Args... args) {
        reg->emplace<T>(id, args)
    }
    template<typename T>
    bool Entity::hasComponent() {
        return false;
    }
    template<typename T>
    T *Entity::getComponent() {
        return nullptr;
    }
}
