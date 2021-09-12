#pragma once

#include "Common.h"

/*
 *  Functions used for rendering inside of the ImGui context
 *  or your own GUI (TODO)
*/
namespace Umbra2D::Gui {
    // display a short description in hoverable bubble
    void HelpMarker(const char* desc);

    // draw texture in ImGui context
    void showTexture(TEXTURE* texture, glm::vec2 targetResolution = glm::vec3(100), glm::vec2 start = glm::vec2(0), glm::vec2 end = glm::vec2(1));
}
