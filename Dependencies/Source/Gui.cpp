#include "Gui.h"
#include "Texture.h"

namespace Umbra2D::Gui {
    void showTexture(TEXTURE* texture, glm::vec2 targetResolution, glm::vec2 start, glm::vec2 end) {

        ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
        ImVec4 border_col = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
        auto my_tex_id = (ImTextureID)texture->getID();
        glm::vec2 resolution = (glm::vec2)texture->getResolution();

        float ratio;

        if (resolution.x > resolution.y) {
            ratio = (resolution.x / targetResolution.x);
        }
        else
            ratio = (resolution.y / targetResolution.y);

        glm::vec2 uvScaleFactors = (glm::vec2(1) - resolution / ratio / targetResolution) / 2.f;

        start -= uvScaleFactors;
        end += uvScaleFactors;

        ImVec2 uv_min = ImVec2(start.x, end.y);                 // Top-left
        ImVec2 uv_max = ImVec2(end.x, start.y);                 // Lower-right

        ImGui::Image(my_tex_id, ImVec2(targetResolution.x, targetResolution.y), uv_min, uv_max, tint_col, border_col);
    }


}
