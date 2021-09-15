#include "Components/PropertyComponent.h"


namespace Umbra2D::Components {
    glm::mat4 toMat4(PositionComponent& c) {
        return glm::translate(glm::mat4(1), glm::vec3(c.translation, c.layer));
    }
    glm::mat4 toMat4(RotationComponent& c) {
        return glm::toMat4(c.rotation);
    }
    glm::mat4 toMat4(ScaleComponent& c) {
        return glm::scale(glm::mat4(1), glm::vec3(c.scale, 1));
    }
}
