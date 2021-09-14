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
    template<typename T>
    void Entity::addComponent(Components::Component *c) {
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
