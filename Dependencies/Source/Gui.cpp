#include "Gui.h"
#include "Texture.h"

namespace Umbra2D::Gui {
        void showTexture(Umbra2D::Assets::Texture* texture, glm::vec2 start, glm::vec2 end) {
            ImVec2 uv_min = ImVec2(start.x, end.y);                 // Top-left
            ImVec2 uv_max = ImVec2(end.x, start.y);                 // Lower-right
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
            ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
            auto my_tex_id = (ImTextureID)texture->getID();
            glm::vec2 resolution = (glm::vec2)texture->getResolution();
            float ratio = std::max(resolution.x, resolution.y) / 600;
            if (ratio > 1)
                ImGui::Image(my_tex_id, ImVec2(resolution.x / ratio, resolution.y / ratio), uv_min, uv_max, tint_col, border_col);
            else ImGui::Image(my_tex_id, ImVec2(resolution.x, resolution.y), uv_min, uv_max, tint_col, border_col);
        }
}
