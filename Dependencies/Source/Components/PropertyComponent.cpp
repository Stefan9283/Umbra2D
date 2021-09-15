#include "Components/PropertyComponent.h"
#include "Entity.h"

namespace Umbra2D::Components {
    glm::mat4 Transform::toMat4() {
        glm::mat4 transform = glm::mat4(1);
        if (allowed.x)
            transform *= glm::translate(glm::mat4(1), glm::vec3(translation, layer));
        else
            transform *= glm::translate(glm::mat4(1), glm::vec3(0, 0, layer));
        if (allowed.y)
            transform *= glm::toMat4(rotation);
        if (allowed.z)
            transform *= glm::scale(glm::mat4(1), glm::vec3(scale, 1));
        return transform;
    }

    void Transform::gui() {
        Component::gui();
        std::string parentID = std::to_string(this->getParent()->getID());
        ImGui::Text("Transform %s", parentID.c_str());
        ImGui::CheckboxFlags(("Allowed Components " + parentID).c_str(), reinterpret_cast<int *>(&this->allowed), 1); // TODO check if it works
        if (allowed.x) {
            ImGui::InputFloat2(("Translation " + parentID).c_str(), reinterpret_cast<float *>(&translation));
            if (ImGui::InputInt(("Translation " + parentID).c_str(), &layer))
                layer = glm::clamp(layer, 0, 999);
        }
        if (allowed.y)
            if (ImGui::SliderFloat4(("Translation " + parentID).c_str(), reinterpret_cast<float *>(&rotation), -1, 1))
                rotation = glm::normalize(rotation);
        if (allowed.z)
            ImGui::InputFloat2(("Translation " + parentID).c_str(), reinterpret_cast<float *>(&scale));
    }
}
