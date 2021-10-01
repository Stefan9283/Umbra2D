#include "Gui/EngineSettings.h"
#define UMBRAINI "umbra.ini"

namespace Umbra2D::Gui {
    void EngineSettings::gui() {
        if (ImGui::Begin("Engine Settings")) {
            if (ImGui::SliderFloat("font size", &textSize, 0.5f, 4.f))
                ImGui::GetIO().FontGlobalScale = textSize;
            theme.gui();
        }
        ImGui::End();
    }

    // TODO load settings from file if available
    EngineSettings::EngineSettings() {
        if (std::filesystem::exists(UMBRAINI)) {
            std::ifstream settings(UMBRAINI);
            std::string line;
            while (std::getline(settings, line)) {
                if (line.starts_with("[TextSize]: ")) {
                    sscanf(line.c_str(), "[TextSize]: %f", &textSize);
                    ImGui::GetIO().FontGlobalScale = textSize;
                } else if (line.starts_with("[ThemeColor]: ")) {
                    glm::vec4 color;
                    sscanf(line.c_str(), "[ThemeColor]: %f %f %f %f", &color.x, &color.y, &color.z, &color.w);
                    theme.setColor(color);
                }
            }
        }

    }

    // TODO save settings to file
    EngineSettings::~EngineSettings() {
        std::ofstream settings(UMBRAINI);
        auto color = getColor();
        settings << "[TextSize]: " << textSize << "\n[ThemeColor]: " << color.x << " " << color.y << " " << color.z << " " << color.w << "\n";
    }

    glm::vec4 EngineSettings::getColor() {
        return theme.getColor();
    }
}