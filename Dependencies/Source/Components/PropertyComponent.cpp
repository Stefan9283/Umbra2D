#include "Components/PropertyComponent.h"


namespace Umbra2D::Components {
    glm::mat4 Transform2D::toMat4() {
        return
                glm::translate(glm::mat4(1), glm::vec3(this->translation.x, this->translation.y, 1)) *
                glm::toMat4(this->rotation) *
                glm::scale(glm::mat4(1), glm::vec3(this->scale.x, this->scale.y, 1));
    }
    void Transform2D::gui(long long unsigned int id) {
        ImGui::SliderFloat2(std::string("translate ").append(std::to_string(id)).c_str(), (float*)&translation, -1000, 1000);
        if (ImGui::SliderFloat4(std::string("rotate ").append(std::to_string(id)).c_str(), (float*)&rotation, -1, 1))
            rotation = glm::normalize(rotation);
        ImGui::SliderFloat2(std::string("scale ").append(std::to_string(id)).c_str(), (float*)&scale, 1, 10000);
        ImGui::SliderInt(std::string("layer ").append(std::to_string(id)).c_str(), &layer, 1, 99);
    }
    void Transform2D::rotate(float degrees) {
        rotation = glm::rotate(rotation, glm::radians(degrees), glm::vec3(0, 0, 1));
    }
}
