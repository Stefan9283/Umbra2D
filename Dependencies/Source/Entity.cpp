#include "Umbra2D.h"

extern Umbra2D::Umbra2DEngine* umbra;

int addingComponentTo = -1;

namespace Umbra2D {

    Entity::Entity(std::string label, Umbra2D::Scene* s) {
        this->scene = s;
        this->id = scene->registry.create();
        this->label = std::move(label);
    }
    uint32_t Entity::getID() {
        return static_cast<std::uint32_t>(id);
    }
    void Entity::gui() {
        ImGui::PushID(getID());
        if (ImGui::TreeNode(label.c_str())) {
            if (ImGui::Button("+") || addingComponentTo == (int)getID()) {
                ImGui::SameLine();
                addingComponentTo = getID();
                int selected = -1;
                const char* items[] = { "Circle", "AARectangle", "Line", "Dynamic", "Static", "Transform" };
                ImGui::Combo("Components", &selected, items, IM_ARRAYSIZE(items));
                if (selected != -1) {
                    switch (selected) {
                        case 0:
                            addComponent<CIRCLE>();
                            break;
                        case 1:
                            addComponent<AARECTANGLE>();
                            break;
                        case 2:
                            addComponent<LINE>();
                            break;
                        case 3:
                            addComponent<DYNAMIC>();
                            break;
                        case 4:
                            addComponent<STATIC>();
                            break;
                        case 5:
                            addComponent<TRANSFORM>();
                            break;
                        case 6:
                            // TODO add scripts
//                            addComponent<SCRIPT>();
                            break;
                    }
                    addingComponentTo = -1;
                }
            }

            if (hasComponent<STATIC>())
                getComponent<STATIC>()->gui();
            if (hasComponent<DYNAMIC>())
                getComponent<DYNAMIC>()->gui();

            if (hasComponent<LINE>())
                getComponent<LINE>()->gui();
            if (hasComponent<CIRCLE>())
                getComponent<CIRCLE>()->gui();
            if (hasComponent<RECTANGLE>())
                getComponent<RECTANGLE>()->gui();
            if (hasComponent<AARECTANGLE>())
                getComponent<AARECTANGLE>()->gui();

            if (hasComponent<TRANSFORM>())
                getComponent<TRANSFORM>()->gui();

            ImGui::TreePop();
        }
        ImGui::PopID();
    }
    Entity::~Entity() {
        scene->registry.destroy(id);
    }
}

