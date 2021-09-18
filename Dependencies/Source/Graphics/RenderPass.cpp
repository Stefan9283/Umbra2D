#include "Graphics/RenderPass.h"
#include "Graphics/FrameBuffer.h"

namespace Umbra2D::Graphics {
    RenderPass::RenderPass(renderpasstype type, glm::ivec2 frbufResolution, int framebufferType) {
        frbuf = new Umbra2D::Graphics::FrameBuffer(framebufferType, frbufResolution);
        this->type = type;
    }
}