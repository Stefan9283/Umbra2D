#include "Fonts.h"
#include "Shader.h"
#include "AssetLibrary.h"
#include "Quad.h"
#include "Engine.h"

extern Umbra2D::Engine* umbra;

namespace Umbra2D::Text {
    Font::Font(std::string path) {
        FT_Library ft;
        if (FT_Init_FreeType(&ft)) {
            std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
            exit(-1);
        }

        FT_Face face;
        if (FT_New_Face(ft, "Dependencies/Assets/Fonts/minecraft.ttf", 0, &face)) {
            std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
            exit(-1);
        }
        FT_Set_Pixel_Sizes(face, 0, 48);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

        for (unsigned char c = 0; c < 128; c++) {
            // load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Umbra2D::Text::Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }

        FT_Done_Face(face);

        FT_Done_FreeType(ft);
    }
    Font::~Font() {
        for (auto c : this->Characters)
            glDeleteTextures(1, &c.second.TextureID);
    }

    void Font::RenderText(Shader* s, std::string text, float x, float y, float scale, glm::vec4 color, float depth) {
        // activate corresponding render state
        s->setVec4("color", color);
        s->setFloat("depth", depth);
        glActiveTexture(GL_TEXTURE0);

        LIBRARY->dq->bindVAO();

        // iterate through all characters
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++) {
            Umbra2D::Text::Character ch = Characters[*c];

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (float)(ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // update VBO for each character
            std::vector<Vertex> vertices{
                    { glm::vec2(xpos, ypos + h ),  glm::vec2(0.0f, 0.0f) },
                    { glm::vec2(xpos,     ypos    ),   glm::vec2(0.0f, 1.0f) },
                    { glm::vec2(xpos + w, ypos),   glm::vec2(1.0f, 1.0f) },

                    { glm::vec2(xpos,     ypos + h),      glm::vec2(0.0f, 0.0f) },
                    { glm::vec2(xpos + w, ypos    ),      glm::vec2(1.0f, 1.0f) },
                    { glm::vec2(xpos + w, ypos + h ),  glm::vec2(1.0f, 0.0f) }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);


            // update content of VBO memory
            LIBRARY->dq->setVBO(vertices.data());
            // render quad
            LIBRARY->dq->draw();
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (float)(ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
