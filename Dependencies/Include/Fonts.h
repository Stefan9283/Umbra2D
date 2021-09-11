#pragma once

#include "Common.h"

namespace Umbra2D::Text {
    struct Character {
        unsigned int TextureID;  // ID handle of the glyph texture
        glm::ivec2   Size;       // Size of glyph
        glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
        unsigned int Advance;    // Offset to advance to next glyph
    };
    class Font {
        public:
        std::map<char, Character> Characters;

        Font(std::string path);
        ~Font();
        void RenderText(Shader* s, std::string text, float x, float y, float scale, glm::vec4 color, float depth);
    };
}
