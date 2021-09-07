#pragma once

#include "Common.h"

/*
 *  Functions used for rendering inside of the ImGui context
 *  or your own GUI (TODO after custom font renderer)
*/

namespace Umbra2D::Gui {
        // draw texture in ImGui context 
        void showTexture(Umbra2D::Assets::Texture* texture, glm::vec2 start = glm::vec2(0), glm::vec2 end = glm::vec2(1));
}
