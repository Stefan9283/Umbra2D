#ifndef UMBRA2D_PROPERTYCOMPONENT_H
#define UMBRA2D_PROPERTYCOMPONENT_H

#include "Common.h"
#include "Component.h"


namespace Umbra2D::Components {
    class PropertyComponent : public Component {
    };
    class Transform2D : public PropertyComponent {
        glm::vec2 scale{1, 1}, translation{};
        glm::quat rotation = glm::quat(glm::vec3(0));
        int layer = 1; // it can be any value in [0, 1000]
        glm::mat4 toMat4();
        void gui(long long unsigned int id);
        // rotates around the Z axis
        void rotate(float degrees);
    };
}

#endif //UMBRA2D_PROPERTYCOMPONENT_H
