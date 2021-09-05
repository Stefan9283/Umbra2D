#pragma once

#include "Common.h"

#define Sprite Texture

namespace Umbra2D {
    class Texture {
     public:
        int id;
        std::string name;
        std::string path;
        glm::vec2 resolution;
        
        Texture(std::string name, std::string path, int id, glm::vec2 resolution);
        Texture(std::string path);
        Texture();
        static Texture loadFromFile(std::string path);
        void destroy();
    };

    class SpriteSheet {
        private:
            std::unordered_map<std::string, std::pair<glm::vec2, glm::vec2>> sprites;
            glm::ivec2 gridSize;
            unsigned int numOfSprites;
        public:
        Texture tex;

        SpriteSheet(std::string pathToImage, glm::vec2 gridSize, unsigned int numSprites);
        void addSpriteDescription(std::string name, unsigned int index);
        std::pair<glm::vec2, glm::vec2> getSpriteCell(unsigned int index);
    };
}
