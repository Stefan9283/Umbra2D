
#ifndef UMBRA2D_FRAMEBUFFER_H
#define UMBRA2D_FRAMEBUFFER_H

#include "Common.h"

namespace Umbra2D::Graphics {
    class FrameBuffer {
    private:
        unsigned int fbo, rbo;
        TEXTURE* texture;
    public:
        /*
         * type can have one of the following values:
         * GL_RED
         * GL_RG
         * GL_RGB
         * GL_RGBA
         */
        FrameBuffer(int type, glm::ivec2 resolution);
        ~FrameBuffer();
        void bind();
        void unbind();
        TEXTURE* getTexture();
    };
};


#endif //UMBRA2D_FRAMEBUFFER_H
