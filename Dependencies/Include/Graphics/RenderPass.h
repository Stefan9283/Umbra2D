#ifndef UMBRA2D_RENDERPASS_H
#define UMBRA2D_RENDERPASS_H

#include "Common.h"
#include "FrameBuffer.h"

enum renderpasstype {
    Void,
    FrBuf,
    Adder
};

namespace Umbra2D::Graphics {
    class RenderPass {
        renderpasstype type;
        Umbra2D::Graphics::FrameBuffer *frbuf;
        Shader* shader;
    public:

        RenderPass(renderpasstype type, glm::ivec2 frbufResolution, int framebufferType = GL_RGBA);
        renderpasstype getType();

        int getTexture();
        void gui();
    };
}

#endif //UMBRA2D_RENDERPASS_H
