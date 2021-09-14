#include "Components/Component.h"
#include "Entity.h"

namespace Umbra2D::Components {
    void Component::setParent(Entity* e) {
        parentEntity = e;
    }
}