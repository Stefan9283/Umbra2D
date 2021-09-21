#include "Umbra2D.h"

namespace Umbra2D::Graphics {
    RenderPass *RenderPass::setType(renderpasstype type) {
        this->type = type;
        return this;
    }
    RenderPass *RenderPass::setFrameBuffer(glm::ivec2 frbufResolution, int framebufferType) {
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
        if (!shader)
            ImGui::Text("Null Shader");
    }
    RenderPass::~RenderPass() {
        delete frbuf;
    }
}