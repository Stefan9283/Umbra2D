#ifndef UMBRA2D_PROPERTYCOMPONENT_H
#define UMBRA2D_PROPERTYCOMPONENT_H

#include "Common.h"
#include "Component.h"


namespace Umbra2D::Components {
    class Transform : public COMPONENT {
    private:
        glm::vec<3, bool> allowed{1, 1, 1};
        glm::vec2 translation{};
        int layer = 1; // it can be any value in [0, 1000]
        glm::quat rotation = glm::quat(glm::vec3(0));
        glm::vec2 scale{1, 1};
    public:
        Transform() = default;
        glm::mat4 toMat4();
        void gui() override;
    };
}

#endif //UMBRA2D_PROPERTYCOMPONENT_H
