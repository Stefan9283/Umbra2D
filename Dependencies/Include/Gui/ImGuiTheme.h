#ifndef UMBRA2D_IMGUITHEME_H
#define UMBRA2D_IMGUITHEME_H

#include "Common.h"
#include "ImGuiElement.h"

namespace Umbra2D::Gui {
    class ImGuiTheme : ImGuiElement {
        glm::vec4 color {};
        std::vector<glm::vec4> defaultColors;
    public:
        ImGuiTheme(glm::vec4 newColor);
        void resetTheme();
        void setColor(glm::vec4 newColor);
        glm::vec4 getColor();
        void gui() override;
    };
}

#endif //UMBRA2D_IMGUITHEME_H
