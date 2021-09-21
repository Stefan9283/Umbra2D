 #pragma once

#include "Common.h"

#define Sprite Texture

namespace Umbra2D::Assets {
    class Animation {
        public:
        std::string name;
        // (sprite index,    time until next sprite (ms))
        std::vector<std::pair<int, float>> frames;

        // returns the index of the closest left sprite
        int getBestFrameInterval(float time);
        float getTotalDuration();
    };

    class Texture {
    private:
        int id = 0;
        std::string path = "NONE";
        glm::ivec2 resolution{0, 0};
    public:
        std::string name = "NAMELESS";

//        Texture(unsigned int id, glm::ivec2 resolution, std::string name);
        // if the second field is omitted by default the name of the texture will be the same as the path
        Texture() = default;
        ~Texture();

        void gui();
        Texture* setTexture(unsigned int id, glm::ivec2 resolution, std::string name);
        Texture* setTexture(std::string path, std::string name = "");
        static std::pair<int, glm::vec2> loadFromFile(std::string path);
        int getID();
        std::string getPath();
        glm::ivec2 getResolution();
    };

    
    class SpriteSheet {
        private:
            glm::ivec2 gridSize;
            unsigned int numOfSprites;
            std::vector<Animation> animations; 
            std::vector<std::string> frameDescriptions;
            unsigned int animationsCount = 0;
    public:
        Texture* tex;

        SpriteSheet(std::string pathToImage, glm::vec2 gridSize = {1, 1}, unsigned int numSprites = 1, std::string name = "");
        ~SpriteSheet();
        void gui();
        
        void addSpriteDescription(std::string name, unsigned int index);
        void addAnimation(Animation anim);
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

        std::vector<Animation> getAnimations();
        Animation& getAnimation(unsigned int index);
        unsigned int getAnimationsCount();

        std::vector<std::string> getFrameDescriptions();
        glm::vec3 getSize();
    };
}
