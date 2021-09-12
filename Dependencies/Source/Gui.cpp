#include "Gui.h"
#include "Texture.h"

namespace Umbra2D::Gui {
    void HelpMarker(const char* desc) {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

 void showTexture(TEXTURE* texture, glm::vec2 targetResolution, glm::vec2 start, glm::vec2 end) {

        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
        ImVec4 border_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        auto my_tex_id = (ImTextureID)texture->getID();
        glm::vec2 resolution = (glm::vec2)texture->getResolution();

        float ratio = resolution.x / resolution.y;

        glm::vec2 mostICanDo;

        mostICanDo.x = ratio * targetResolution.y;
        mostICanDo.y = targetResolution.x / ratio;

        glm::vec2 newResolution;

        if (mostICanDo.x < targetResolution.x) {
            newResolution = glm::vec2(mostICanDo.x, targetResolution.y);
        }
        else {
            newResolution = glm::vec2(targetResolution.x, mostICanDo.y);
        }

        ImVec2 uv_min = ImVec2(start.x, end.y); // Top-left
        ImVec2 uv_max = ImVec2(end.x, start.y); // Lower-right

        ImGui::Image(my_tex_id, ImVec2(newResolution.x, newResolution.y), uv_min, uv_max, tint_col, border_col);
    }


}
