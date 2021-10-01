
#include <Gui/Editor.h>

#include "Umbra2D.h"

extern Umbra2D::Umbra2DEngine* umbra;

namespace Umbra2D::Gui {
    Editor::Editor(Window* window) {
        cam = new Umbra2D::Components::Camera(window);
    }
    Editor::~Editor() {
        delete cam;
    }
    void Editor::gui() {
        // DRAW FRAMEBUFFER AS IMGUI TEXTURE
        if (ImGui::Begin("Editor", (bool*)true, ImGuiWindowFlags_NoScrollbar) && frbuf) {
            glm::vec2 resolution = frbuf->getTexture()->getResolution();
            ImVec2 windowSize = ImGui::GetWindowSize();

            auto targetResolution = glm::vec2(windowSize.x, windowSize.y);

            float ratio = resolution.x / resolution.y;

            glm::vec2 mostICanDo;

            mostICanDo.x = ratio * targetResolution.y;
            mostICanDo.y = targetResolution.x / ratio;

            glm::vec2 newResolution;

            if (mostICanDo.x < targetResolution.x) {
                newResolution = glm::vec2(mostICanDo.x, targetResolution.y);
            } else {
                newResolution = glm::vec2(targetResolution.x, mostICanDo.y);
            }

            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImGui::SetCursorPos(ImVec2((windowSize.x - newResolution.x) / 2, (windowSize.y - newResolution.y) / 2));
            Umbra2D::Gui::showTexture(frbuf->getTexture(), targetResolution);
            ImVec2 pos2 = ImGui::GetCursorScreenPos();
            if (ImGui::IsItemHovered()) {
                ImGui::BeginTooltip();
                ImGuiIO& io = ImGui::GetIO();
                if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
                    auto delta = ImGui::GetMouseDragDelta(0, 6.0f);
//                    std::cout << delta.x << " " << delta.y << "\n";

                    auto dragInViewPortOld = glm::vec2(io.MousePos.x - pos.x - delta.x, pos2.y - io.MousePos.y + delta.y - ImGui::GetStyle().ItemSpacing.y);
                    auto dragInViewPortNew = glm::vec2(io.MousePos.x - pos.x, pos2.y - io.MousePos.y - ImGui::GetStyle().ItemSpacing.y);

                    auto normalizedDragOld = (2.f * dragInViewPortOld - newResolution) / newResolution;
                    auto normalizedDragNew = (2.f * dragInViewPortNew - newResolution) / newResolution;

                    auto CoordsInWorldOld = cam->getWorldCoords(normalizedDragOld);
                    auto CoordsInWorldNew = cam->getWorldCoords(normalizedDragNew);

                    auto deltaDist = CoordsInWorldNew - CoordsInWorldOld;
                    // TODO use this distance to drag objects using the mouse or for editor camera movement
//                    std::cout << glm::to_string(deltaDist) << "\n";
                }
                auto posOnViewPort = glm::vec2(io.MousePos.x - pos.x, pos2.y - io.MousePos.y - ImGui::GetStyle().ItemSpacing.y);
//                ImGui::Text("Coords %f, %f", posOnViewPort.x, posOnViewPort.y);
//                ImGui::Text("Resolution %f, %f", newResolution.x, newResolution.y);

                auto normalizedCoords = (2.f * posOnViewPort - newResolution) / newResolution;

//                ImGui::Text("Coords in [-1, 1] %f, %f", normalizedCoords.x, normalizedCoords.y);
                auto worldCoords = cam->getWorldCoords(normalizedCoords);
                ImGui::Text("World Coords %f, %f", worldCoords.x, worldCoords.y);
                ImGui::EndTooltip();
            }
        }
        ImGui::End();
    }

    glm::mat4 Editor::getProj() { return cam->getProj(); }
    glm::mat4 Editor::getView() { return cam->getView(); }

    void Editor::setFrameBuffer(Umbra2D::Graphics::FrameBuffer* pFrameBuffer) {
        this->frbuf = pFrameBuffer;
    }

    Umbra2D::Components::Camera *Editor::getCamera() {
        return this->cam;
    }

}
