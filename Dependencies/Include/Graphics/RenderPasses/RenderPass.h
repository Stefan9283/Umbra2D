#ifndef UMBRA2D_RENDERPASS_H
#define UMBRA2D_RENDERPASS_H

#include "Common.h"
#include "Graphics/FrameBuffer.h"

enum RenderPassInputType {
    Void,
    Filter,
    Adder
};


namespace Umbra2D::Graphics {
    class RenderPass {
        std::string label = "";
        RenderPassInputType type;
        Umbra2D::Graphics::FrameBuffer *frbuf = nullptr;
        Shader* shader = nullptr;
    public:
        RenderPass(RenderPassInputType type);
        ~RenderPass();

        RenderPass* setFrameBuffer(glm::ivec2 frbufResolution, int framebufferType = GL_RGBA);
        FrameBuffer* getFrameBuffer();
        int getTexture();

        Shader* getShader();

        RenderPassInputType getType();

        virtual void render(Umbra2D::Components::Camera* cam, Scene* s) = 0;
        void render(Umbra2D::Components::Camera* cam, Scene* s, FrameBuffer* fb);
        void render(Umbra2D::Components::Camera* cam, Scene* s, FrameBuffer* fb1, FrameBuffer* fb2);

        void gui();
    protected:
    };
}

#endif //UMBRA2D_RENDERPASS_H
