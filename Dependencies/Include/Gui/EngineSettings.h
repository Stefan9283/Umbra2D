#ifndef UMBRA2D_ENGINESETTINGS_H
#define UMBRA2D_ENGINESETTINGS_H

#include "Common.h"
#include "ImGuiElement.h"
#include "ImGuiTheme.h"

namespace Umbra2D::Gui {
    class EngineSettings : public ImGuiElement {
        float textSize = 1;
        ImGuiTheme theme;
    public:
        EngineSettings();
        ~EngineSettings();
        glm::vec4 getColor();
        void gui() override;
    };
}
#endif //UMBRA2D_ENGINESETTINGS_H
