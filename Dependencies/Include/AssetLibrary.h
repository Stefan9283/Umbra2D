#pragma once

#include "Common.h" 

/*
 *  A complete database of all the assets needed 
 *  - all the simple textures used for rendering
 *    static objects
 *  - sprite sheets for dynamic objects
 *  - a unit quad used for rendering any in-game object
 */
namespace Umbra2D {
    class AssetLibrary {
        public:
        std::vector<Umbra2D::Assets::Texture*> textures;
        std::vector<Umbra2D::Assets::SpriteSheet*> spriteSheets;

        Quad* q;
        TEXTURE* defaultTexture;

        void gui();

        AssetLibrary();
        ~AssetLibrary();

        unsigned int addSpriteSheet(std::string path, glm::vec2 gridSize, unsigned int numSprites, std::string name = "");
        unsigned int addTexture(std::string path, std::string name = "");
    };
}
