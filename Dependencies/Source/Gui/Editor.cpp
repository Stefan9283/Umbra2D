#include <Gui/Gui.h>
#include "Gui/Editor.h"
#include "Components/Camera.h"
#include "Graphics/FrameBuffer.h"
#include "Texture.h"
#include "Engines/Engine.h"

extern Umbra2D::Umbra2DEngine* umbra;

namespace Umbra2D::Gui {
    Editor::Editor(Window* window) {
        frbuf = new Umbra2D::FrameBuffer(GL_RGBA, {1920, 1080});
        cam = new Umbra2D::Components::Camera(window);
    }
    void Editor::gui() {
        // DRAW FRAMEBUFFER AS IMGUI TEXTURE
        if (ImGui::Begin("Editor", (bool*)true, ImGuiWindowFlags_NoScrollbar)) {
            ImVec2 windowSize = ImGui::GetWindowSize();

            auto targetResolution = glm::vec2(windowSize.x, windowSize.y);
            glm::vec2 resolution = frbuf->getTexture()->getResolution();

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

    void Editor::startRender() {
        frbuf->bind();
        glm::vec4 color = umbra->getThemeColor();
        glClearColor(color.r, color.g, color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Editor::stopRender() { frbuf->unbind(); }
}
