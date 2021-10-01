
#include <Gui/ImGuiTheme.h>

#include "Umbra2D.h"

void Umbra2D::Gui::ImGuiTheme::resetTheme() {
    auto defaultColor = defaultColors[7];

    std::vector<unsigned int> changeAccentsAtTheseIndices{7, 15, 18, 21, 24, 27, 30, 33, 36, 49};

    for (auto i : changeAccentsAtTheseIndices) {
        for (int j = 0; j < 3; j++) {
            auto currentColor = defaultColors[i + j];
            auto newColor = (currentColor / defaultColor) * color;
            ImGui::GetStyle().Colors[i + j] = ImVec4(newColor.x, newColor.y, newColor.z, newColor.w);
        }
    }
    ImGui::GetStyle().Colors[11] = ImVec4(0, 0, 0, 1);
}

void Umbra2D::Gui::ImGuiTheme::gui() {
    ImGui::BeginChild("Theme");
    if (ImGui::ColorEdit4("ThemeColor", reinterpret_cast<float *>(&color)))
        setColor(color);

    // THEME COLORS
    ImGuiStyle& style = ImGui::GetStyle();

    static ImGuiColorEditFlags alpha_flags = 0;
    if (ImGui::RadioButton("Opaque", alpha_flags == ImGuiColorEditFlags_None))             { alpha_flags = ImGuiColorEditFlags_None; } ImGui::SameLine();
    if (ImGui::RadioButton("Alpha",  alpha_flags == ImGuiColorEditFlags_AlphaPreview))     { alpha_flags = ImGuiColorEditFlags_AlphaPreview; } ImGui::SameLine();
    if (ImGui::RadioButton("Both",   alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf)) { alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf; } ImGui::SameLine();

    Umbra2D::Gui::HelpMarker(
            "In the color list:\n"
            "Left-click on color square to open color picker,\n"
            "Right-click to open edit options menu.");

    static ImGuiTextFilter filter;
    filter.Draw("Filter colors", ImGui::GetFontSize() * 16);

    for (int i = 0; i < ImGuiCol_COUNT; i++) {
        const char* name = ImGui::GetStyleColorName(i);
        ImGui::ColorEdit4((name + std::to_string(i)).c_str(), (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
    }

    ImGui::EndChild();
}

Umbra2D::Gui::ImGuiTheme::ImGuiTheme() {
    storeDefaultColors();
    setColor({0.4, 0., 0.3, 1});
}

void Umbra2D::Gui::ImGuiTheme::setColor(glm::vec4 newColor) {
    this->color = newColor;
    resetTheme();
}
glm::vec4 Umbra2D::Gui::ImGuiTheme::getColor() { return color; }

void Umbra2D::Gui::ImGuiTheme::storeDefaultColors() {
    defaultColors.resize(55);
    auto style = ImGui::GetStyle();
    for (int i = 0; i < 55; i++)
        defaultColors[i] = glm::vec4(style.Colors[i].x, style.Colors[i].y, style.Colors[i].z, style.Colors[i].w);
}

