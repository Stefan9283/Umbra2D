
#include "Camera.h"
#include "Window.h"

namespace Umbra2D {
    Camera::Camera(Umbra2D::Window* window) {
        windowReference = window;
        UpdateProjMatrix();
        UpdateViewMatrix();
    }
    void Camera::UpdateProjMatrix() {
        glm::vec<2, double> size = 0.5 * scaleFactor * windowReference->getSize();
        proj = glm::ortho(- size.x, size.x, -size.y, size.y, 0.01, 999999.);
    }
    void Camera::UpdateViewMatrix() {
        view = glm::translate(glm::mat4(1), glm::vec3(position.x, position.y, 0.f));
    }
    glm::mat4 Camera::getView() {
        return view;
    }
    glm::mat4 Camera::getProj() {
        return proj;
    }
    void Camera::MoveVertically(float units) {
        position.y -= units;
        UpdateViewMatrix();
    }
    void Camera::MoveHorizontally(float units) {
        position.x += units;
        UpdateViewMatrix();
    }
    void Camera::Zoom(float zoom) {
        scaleFactor -= zoom;
        UpdateProjMatrix();
    }

} 