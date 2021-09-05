#pragma once

#include "Common.h"

/*
 *  Functions used for rendering inside of the ImGui context
 *  or your own GUI (TODO after custom font renderer)
*/

namespace Umbra2D {
    class Texture;
    namespace Gui {
        // draw texture in ImGui context 
        void showTexture(Umbra2D::Texture& texture);
    };
}