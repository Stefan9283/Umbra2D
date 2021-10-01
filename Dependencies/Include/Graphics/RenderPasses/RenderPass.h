#ifndef UMBRA2D_RENDERPASS_H
#define UMBRA2D_RENDERPASS_H

#include "Common.h"
#include "Graphics/FrameBuffer.h"

enum renderpasstype {
    Void,
    FrBuf,
    Adder
};

namespace Umbra2D::Graphics {
    class RenderPass {
        renderpasstype type;
        Umbra2D::Graphics::FrameBuffer *frbuf = nullptr;
        Shader* shader = nullptr;
    public:
        RenderPass(renderpasstype type);
        ~RenderPass();

        RenderPass* setFrameBuffer(glm::ivec2 frbufResolution, int framebufferType = GL_RGBA);
        FrameBuffer* getFrameBuffer();
        int getTexture();

        RenderPass* setShader(SHADER* shader);
        Shader* getShader();

        renderpasstype getType();

        virtual void render(Umbra2D::Components::Camera* cam, Scene* s) = 0;
        void render(Umbra2D::Components::Camera* cam, Scene* s, FrameBuffer* fb);
        void render(Umbra2D::Components::Camera* cam, Scene* s, FrameBuffer* fb1, FrameBuffer* fb2);

        void gui();
    protected:
    };
}

#endif //UMBRA2D_RENDERPASS_H
