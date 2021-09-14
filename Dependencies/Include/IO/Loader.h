#pragma once

#include "Common.h"

namespace Umbra2D {
    class Loader {
    private:
        std::string path;
        char buffer[MAX_LEN];

        struct TextureInfo {
            std::string name, path;
        };

        struct SpriteSheetInfo {
            int noOfSprites;
            glm::ivec2 gridSize;
            TextureInfo textureInfo;

            std::vector<ANIMATION> animations;
            std::vector<std::string> frameDescriptions;
        };

        void parseTexture(TextureInfo& textureInfo);

        void parseSpriteSize(int& noOfSprites, glm::ivec2& gridSize);

        void parseAnimationName(std::string& name);

        void parseKeyFrame(int& index, float& timeUntilNextFrame);

        void parseFrameDescription(std::string& frameDescription);

        void parseKeyFrames(std::ifstream& fin, std::vector<std::pair<int, float>>& keyFrames);

        void parseAnimation(std::ifstream& fin, std::vector<ANIMATION>& animations);

        void parseAnimations(std::ifstream& fin, std::vector<ANIMATION>& animations);

        void parseFrameDescriptions(std::ifstream& fin, std::vector<std::string>& frameDescriptions);

        void parseSpriteSheet(std::ifstream& fin, SpriteSheetInfo& spriteSheetInfo);

        void parseTextures(std::ifstream& fin);

        void parseSpriteSheets(std::ifstream& fin);

        void parseAssetLibrary(std::ifstream& fin);

    public:
        Loader(std::string path);

        void parseInputFile();
    };
}
