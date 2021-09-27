#include "Umbra2D.h"

namespace Umbra2D::Components {
    glm::mat4 Transform::toMat4() {
        glm::mat4 transform = glm::mat4(1);
        if (allowed.x)
            transform *= glm::translate(glm::mat4(1), glm::vec3(translation, -layer));
        else
            transform *= glm::translate(glm::mat4(1), glm::vec3(0, 0, -layer));
        if (allowed.y)
            transform *= glm::toMat4(rotation);
        if (allowed.z)
            transform *= glm::scale(glm::mat4(1), glm::vec3(scale, 1));
        return transform;
    }
    void Transform::gui() {
        if (ImGui::TreeNode("Transform")) {
            ImGui::Text("Transform");
            ImGui::Checkbox("Allowed Translaton", &allowed.x);
            ImGui::SameLine();
            ImGui::Checkbox("Allowed Rotation", &allowed.y);
            ImGui::SameLine();
            ImGui::Checkbox("Allowed Scaling", &allowed.z);

            if (allowed.x) {
                ImGui::InputFloat2("Translation", reinterpret_cast<float *>(&translation));
            }
            if (ImGui::InputInt("Layer", &layer))
                layer = glm::clamp(layer, 0, 999);
            if (allowed.y)
                if (ImGui::SliderFloat4("Rotation ", reinterpret_cast<float *>(&rotation), -1, 1))
                    rotation = glm::normalize(rotation);
            if (allowed.z)
                ImGui::InputFloat2("Scale ", reinterpret_cast<float *>(&scale));
            ImGui::TreePop();
        }
    }
}
