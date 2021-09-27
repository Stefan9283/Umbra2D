#include "Umbra2D.h"
#include "Script.h"

namespace Umbra2D {
    Script::Script() {
        lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::package);
    }
    Script *Script::readFromFile(std::string path) {
        if (std::filesystem::exists(path)) {
            this->path = path;
            IO::loadFile(asText, path);
            needsReload = false;
        }
        return this;
    }

    void Script::evaluate() {
        lua.script(asText);
    }

    void Script::gui() {
        ImGui::InputText("Label", &label);
        if (ImGui::InputTextMultiline(label.c_str(), &asText))
            needsReload = true;
        if (ImGui::Button("Reload Script"))
            readFromFile(path);
        if (ImGui::Button("Save To File")) {
            readFromFile(path);
            IO::saveFile(asText, path);
        }
    }
}