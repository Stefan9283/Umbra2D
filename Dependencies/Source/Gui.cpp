#include "Gui.h"
#include "Texture.h"

namespace Umbra2D {
namespace Gui {
        void showTexture(Umbra2D::Assets::Texture* texture) {
            ImVec2 uv_min = ImVec2(0.0f, 1.0f);                 // Top-left
            ImVec2 uv_max = ImVec2(1.0f, 0.0f);                 // Lower-right
            ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
            ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f); // 50% opaque white
            ImTextureID my_tex_id = (ImTextureID)texture->id;
            int ratio = std::max(texture->resolution.x, texture->resolution.y) / 600;
            if (ratio > 1)
                ImGui::Image(my_tex_id, ImVec2(texture->resolution.x / ratio, texture->resolution.y / ratio), uv_min, uv_max, tint_col, border_col);
            else ImGui::Image(my_tex_id, ImVec2(texture->resolution.x, texture->resolution.y), uv_min, uv_max, tint_col, border_col);
        }
}
}
