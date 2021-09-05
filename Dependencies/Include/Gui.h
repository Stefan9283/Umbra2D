#pragma once

#include "Common.h"

namespace Umbra2D {
    class Texture;
    namespace Gui {
        // draw texture in ImGui context 
        void showTexture(Umbra2D::Texture& texture);
    };
}