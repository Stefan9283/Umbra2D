#pragma once

#include "Common.h"

/*
 *  Functions used for rendering inside of the ImGui context
 *  or your own GUI (TODO)
*/

#define TEXTURE_PAYLOAD 0
#define SPRITESHEET_PAYLOAD 1
#define DYNAMIC_ENTITY 2
#define STATIC_ENTITY 3


namespace Umbra2D::Gui {
    void HelpMarker(const char* desc);
    // draw texture in ImGui context

    void showTexture(TEXTURE* texture, glm::vec2 targetResolution = glm::vec3(100), glm::vec2 start = glm::vec2(0), glm::vec2 end = glm::vec2(1));

    // TODO
    class DragAndDropPayload {
    public:
        char type;
        void* data;
    };
}
