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
    class Texture;
    class SpriteSheet;
    class Quad;

    class AssetLibrary {
        public:
        std::vector<Texture*> textures;
        std::vector<SpriteSheet*> spriteSheets;
        Quad* q;

        void gui();

        AssetLibrary();
        
        void addSpriteSheet(std::string path, glm::vec2 gridSize, unsigned int numSprites);
        void addTexture(std::string path);
    };
}
