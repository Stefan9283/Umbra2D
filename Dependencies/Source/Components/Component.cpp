#include "Umbra2D.h"

namespace Umbra2D::Components {
    void Component::setParent(Entity* e) {
        parentEntity = e;
    }
    Entity *Component::getParent() {
        return parentEntity;
    }
}
