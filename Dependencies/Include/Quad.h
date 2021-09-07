#ifndef UMBRA2D_QUAD_H
#define UMBRA2D_QUAD_H

#include "Common.h"

/*
 *   a simple unit length quad on which sprites could be rendered
 */

namespace Umbra2D {
    class Quad {
    private:
        unsigned int VAO, VBO, EBO;
    public:
        // creates a mesh for a unit length quad
        Quad();
        // Draws the quad
        void draw();
        void drawN(unsigned int N);
    };
}

#endif //UMBRA2D_QUAD_H
