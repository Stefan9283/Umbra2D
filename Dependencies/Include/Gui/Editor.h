#ifndef UMBRA2D_EDITOR_H
#define UMBRA2D_EDITOR_H
#include "Common.h"
#include "ImGuiElement.h"

namespace Umbra2D::Gui {
    class Editor : public ImGuiElement {
    private:
        Umbra2D::Graphics::FrameBuffer *frbuf;
        Umbra2D::Components::Camera* cam;
    public:
        explicit Editor(Window* window);
        ~Editor();
        void gui() override;
        void startRender();
        void stopRender();
        glm::mat4 getProj();
        glm::mat4 getView();
    };
}

#endif //UMBRA2D_EDITOR_H
