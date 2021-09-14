#ifndef UMBRA2D_PROPERTYCOMPONENT_H
#define UMBRA2D_PROPERTYCOMPONENT_H

#include "Common.h"
#include "Component.h"


namespace Umbra2D::Components {
    struct PositionComponent {
        glm::vec2 translation{};
        int layer = 1; // it can be any value in [0, 1000]
    };
    struct RotationComponent {
        glm::quat rotation = glm::quat(glm::vec3(0));
    };
    struct ScaleComponent {
        glm::vec2 scale{1, 1};
    };
}

#endif //UMBRA2D_PROPERTYCOMPONENT_H
