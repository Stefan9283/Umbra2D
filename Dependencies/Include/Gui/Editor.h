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
        Umbra2D::Components::Camera* getCamera();
        glm::mat4 getProj();
        glm::mat4 getView();
        void setFrameBuffer(Umbra2D::Graphics::FrameBuffer* pFrameBuffer);
    };
}

#endif //UMBRA2D_EDITOR_H
