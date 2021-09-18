#ifndef UMBRA2D_QUAD_H
#define UMBRA2D_QUAD_H

#include "Common.h"

/*
 *   a simple unit length quad on which sprites could be rendered
 */

struct Vertex {
    glm::vec2 position;
    glm::vec2 texture;
};

namespace Umbra2D::Graphics {
    class Quad {
    private:
        unsigned int VAO, VBO, EBO;
    public:
        // creates a mesh for a unit length quad
        Quad();
        ~Quad();
        // Draws the quad
        void draw();
        void drawN(unsigned int N);
    };

    // used for text rendering
    class DynamicQuad {
    private:
            unsigned int VAO, VBO;
    public:
        DynamicQuad();
        ~DynamicQuad();
        void bindVAO();
        void setVBO(Vertex* vertices);
        void draw();
    };

}

#endif //UMBRA2D_QUAD_H
