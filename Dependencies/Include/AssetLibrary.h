#pragma once

#include "Common.h" 

/*
 *  A complete database of all the assets needed 
 *  - all the simple textures used for rendering
 *    static objects
 *  - sprite sheets for dynamic objects
 *  - shaders used in various render passes
 *  - a unit quad used for rendering any in-game object
 */
namespace Umbra2D {
    class AssetLibrary {
        public:
        std::vector<TEXTURE*> textures;
        std::vector<SPRITE_SHEET*> spriteSheets;
        std::vector<Umbra2D::Graphics::Shader*> shaders;

        Umbra2D::Graphics::Quad* q;
        Umbra2D::Graphics::DynamicQuad* dq;

        TEXTURE* defaultTexture;

        void gui();

        AssetLibrary();
        ~AssetLibrary();

        unsigned int addSpriteSheet(const std::string& path, glm::vec2 gridSize, unsigned int numSprites, std::string name = "");
        unsigned int addTexture(const std::string& path, std::string name = "");
        unsigned int addShader(const std::string& name, const std::string& pathv, const std::string& pathf);
    };
}
