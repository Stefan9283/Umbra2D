#pragma once

#include "Common.h"

#define Sprite Texture

namespace Umbra2D::Assets {
    class Animation {
        public:
        std::string name;
        // (sprite index,    time until next sprite)
        std::vector<std::pair<int, float>> frames;
    };

    class Texture {
     public:
        int id;
        std::string name;
        std::string path;
        glm::ivec2 resolution;

        // if the second field is ommited by default the name of the texture will be the same as the path
        Texture(std::string path, std::string name = "");
        void gui();
        static std::pair<int, glm::vec2> loadFromFile(std::string path);
        void destroy();
    };

    
    class SpriteSheet {
        private:
            glm::ivec2 gridSize;
            unsigned int numOfSprites;
            std::vector<Animation> animations; 
            std::vector<std::string> frameDescriptions;
        public:
        Texture* tex;

        SpriteSheet(std::string pathToImage, glm::vec2 gridSize, unsigned int numSprites, std::string name = "");
        void gui();
        
        void addSpriteDescription(std::string name, unsigned int index);
        /*
         *    Example of sprite cell indexing on a simple prite sheet        
         *    
         *     [0] [1]  [2]  [3] 
         *     [4] [5]  [6]  [7] 
         *     [8] [9] [10] [11] 
         *    [12] [13]
         *
         *    Expected behavior: when asking for the 14th or 16th cell 
         *    the function will loop back and return [0]'s and [2]'s coords
         */
        std::pair<glm::vec2, glm::vec2> getSpriteCell(unsigned int index);
    };
}
