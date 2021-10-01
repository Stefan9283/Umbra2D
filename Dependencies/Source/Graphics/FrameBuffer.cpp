#include "Umbra2D.h"

extern Umbra2D::Umbra2DEngine* umbra;

namespace Umbra2D::Graphics {
    FrameBuffer::FrameBuffer(int type, glm::ivec2 resolution) {
        this->type = type;
        // framebuffer configuration
        // -------------------------
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo); // or bind();
        // create a color attachment texture
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, type, resolution.x, resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
        // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, resolution.x, resolution.y); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
        // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";
        glBindFramebuffer(GL_FRAMEBUFFER, 0);  // or unbind();

        texture = (new TEXTURE)->setTexture(textureID, resolution, "framebuffer");
    }
    FrameBuffer::~FrameBuffer() {
        delete texture;
        glDeleteRenderbuffers(1, &rbo);
        glDeleteFramebuffers(1, &fbo);
    }
    void FrameBuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glm::ivec2 resolution = texture->getResolution();
        glViewport(0, 0, resolution.x, resolution.y);
    }
    void FrameBuffer::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glm::ivec2 resolution = WINDOW->getSize();
        glViewport(0, 0, resolution.x, resolution.y);
    }
    TEXTURE* FrameBuffer::getTexture() {
        return texture;
    }
}