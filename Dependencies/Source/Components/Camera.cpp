
#include "Components/Camera.h"
#include "Window.h"

namespace Umbra2D::Components {
    Camera::Camera(Umbra2D::Window* window) {
        windowReference = window;
        UpdateProjMatrix();
        UpdateViewMatrix();
    }
    void Camera::gui() {
        if (ImGui::DragFloat2("Camera Pos", (float*)&position, -1000, 1000))
            UpdateViewMatrix();
        if (ImGui::DragFloat("Camera Zoom", &this->scaleFactor, 1, 1000))
            UpdateProjMatrix();
    }
    void Camera::UpdateProjMatrix() {
        glm::vec2 size = - 0.5f * scaleFactor * windowReference->getSize();
        proj = glm::ortho(size.x, - size.x, size.y, -size.y, nearZ, farZ * 2);
    }
    void Camera::UpdateViewMatrix() {
        view = glm::translate(glm::mat4(1), glm::vec3(- position.x, - position.y, 0.f));
    }
    glm::mat4 Camera::getView() {
        return view;
    }
    glm::mat4 Camera::getProj() {
        return proj;
    }
    void Camera::MoveVertically(float units) {
        position.y += units;
        UpdateViewMatrix();
    }
    void Camera::MoveHorizontally(float units) {
        position.x -= units;
        UpdateViewMatrix();
    }
    void Camera::Zoom(float zoom) {
        scaleFactor -= zoom;
        UpdateProjMatrix();
    }
    glm::vec2 Camera::getWorldCoords(glm::vec2 norm) {
        glm::vec2 size = 0.5f * scaleFactor * windowReference->getSize();
        return position + norm * size;
    }
}
