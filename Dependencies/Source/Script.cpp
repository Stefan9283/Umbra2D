#include "Umbra2D.h"
#include "Script.h"

Umbra2D::Script *Umbra2D::Script::readFromFile(std::string path) {
    if (std::filesystem::exists(path)) {
        this->path = path;
        IO::loadFile(asText, path);
        needsReload = false;
    }
    return this;
}

void Umbra2D::Script::evaluate() {
//    asScript.eval(asText);
}

void Umbra2D::Script::gui() {
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
