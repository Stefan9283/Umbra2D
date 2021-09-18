#ifndef UMBRA2D_RENDERPASS_H
#define UMBRA2D_RENDERPASS_H

#include "Common.h"
#include "FrameBuffer.h"

namespace Umbra2D::Graphics {
    class RenderPass {
    public:
        enum renderpasstype {
            Void,
            FrBuf,
            Adder
        };
        renderpasstype type;
        Umbra2D::Graphics::FrameBuffer *frbuf;

        RenderPass(renderpasstype type, glm::ivec2 frbufResolution, int framebufferType = GL_RGBA);
    };
}

#endif //UMBRA2D_RENDERPASS_H
