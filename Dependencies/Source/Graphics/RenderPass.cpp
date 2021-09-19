#include "Graphics/RenderPass.h"
#include "Graphics/FrameBuffer.h"
#include "Graphics/Shader.h"
#include "Texture.h"

namespace Umbra2D::Graphics {
    RenderPass::RenderPass(renderpasstype type, glm::ivec2 frbufResolution, int framebufferType) {
        frbuf = new Umbra2D::Graphics::FrameBuffer(framebufferType, frbufResolution);
        this->type = type;
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
}