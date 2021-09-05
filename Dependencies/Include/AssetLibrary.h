#pragma once

#include "Common.h" 

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
