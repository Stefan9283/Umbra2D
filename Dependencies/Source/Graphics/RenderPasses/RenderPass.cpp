
#include "Umbra2D.h"

namespace Umbra2D::Graphics {
    RenderPass *RenderPass::setFrameBuffer(glm::ivec2 frbufResolution, int framebufferType) {
        delete frbuf;
        frbuf = new Umbra2D::Graphics::FrameBuffer(framebufferType, frbufResolution);
        return this;
    }
    renderpasstype RenderPass::getType() { return type; }
    int RenderPass::getTexture() { return frbuf->getTexture()->getID(); }

    void RenderPass::gui() {
        switch (type) {
            case Adder:
                ImGui::Text("Type: Adder");
                break;
            case FrBuf:
                ImGui::Text("Type: FrBuf");
                break;
            case Void:
                ImGui::Text("Type: Void");
                break;
        }

        std::string shaderInfo;
        if (!shader) {
            shaderInfo = "Null Shader";
        } else {
            shaderInfo = "Shader - " + shader->getName();
        }
        ImGui::Button(shaderInfo.c_str());
        if (ImGui::BeginDragDropTarget()) {
            if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("SHADER_PTR")) {
                this->shader = *(Umbra2D::Graphics::Shader**) payload->Data;
            }
            ImGui::EndDragDropTarget();
        }
        Umbra2D::Gui::showTexture(frbuf->getTexture());
    }
    RenderPass::~RenderPass() {
        delete frbuf;
    }
    FrameBuffer *RenderPass::getFrameBuffer() {
        return frbuf;
    }

    Shader *RenderPass::getShader() {
        return shader;
    }

    void RenderPass::render(Umbra2D::Components::Camera* cam, Scene* s, FrameBuffer *fb) {
        if (!shader) return;
        shader->setTexture("tex1", fb->getTexture()->getID(), 0);
        render(cam, s);
        shader->setTexture("tex1", 0, 0);
    }
    void RenderPass::render(Umbra2D::Components::Camera* cam, Scene* s, FrameBuffer *fb1, FrameBuffer *fb2) {
        if (!shader) return;
        shader->setTexture("tex2", fb2->getTexture()->getID(), 1);
        render(cam, s, fb1);
        shader->setTexture("tex2", 0, 1);
    }

    RenderPass::RenderPass(renderpasstype type) {
        this->type = type;
        this->frbuf = new FrameBuffer(GL_RGBA, {1,1});
    }
}
