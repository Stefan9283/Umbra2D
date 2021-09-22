#include "Umbra2D.h"
#include "Script.h"

Umbra2D::Script *Umbra2D::Script::readFromFile(std::string path) {
    if (std::filesystem::exists(path)) {
        this->path = true;
        IO::loadFile(asText, path);
        asText = path;
    }
    return this;
}

void Umbra2D::Script::evaluate() {
//    if (path)
//        asScript.eval_file(asText);
//    else asScript.eval(asText);
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
