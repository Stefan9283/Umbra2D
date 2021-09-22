#pragma once

#include "Common.h"

namespace Umbra2D::IO {
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

        struct ShaderInfo {
            std::string name, path_v, path_f;
        };

        void parseKeyFrame(int& index, float& timeUntilNextFrame);
        void parseKeyFrames(std::ifstream& fin, std::vector<std::pair<int, float>>& keyFrames);

        void parseAnimationName(std::string& name);
        void parseAnimation(std::ifstream& fin, std::vector<ANIMATION>& animations);
        void parseAnimations(std::ifstream& fin, std::vector<ANIMATION>& animations);

        void parseFrameDescription(std::string& frameDescription);
        void parseFrameDescriptions(std::ifstream& fin, std::vector<std::string>& frameDescriptions);

        void parseTexture(TextureInfo& textureInfo);
        void parseTextures(std::ifstream& fin);

        void parseSpriteSize(int& noOfSprites, glm::ivec2& gridSize);
        void parseSpriteSheet(std::ifstream& fin, SpriteSheetInfo& spriteSheetInfo);
        void parseSpriteSheets(std::ifstream& fin);

        void parseShader(ShaderInfo& shaderInfo);
        void parseShaders(std::ifstream& fin);

        void parseAssetLibrary(std::ifstream& fin);

    public:
        Loader(std::string path);

        void parseInputFile();
    };
}
