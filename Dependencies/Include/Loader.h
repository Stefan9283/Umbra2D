#pragma once

#include "Common.h"

namespace Umbra2D {
    class Loader {
    private:
        std::string path;
        char buffer[MAX_LEN];

        struct TextureInfo {
            std::string name, path;

            friend std::ostream& operator<<(std::ostream& os, const TextureInfo& textureInfo) {
                os << textureInfo.name << " " << textureInfo.path << "\n";
                return os;
            }
        };

        struct SpriteSheetInfo {
            int noOfSprites;
            glm::ivec2 gridSize;
            TextureInfo textureInfo;

            std::vector<std::pair<std::string, std::vector<std::pair<int, float>>>> animations;
            std::vector<std::string> frameDescriptions;

            friend std::ostream& operator<<(std::ostream& os, const SpriteSheetInfo& spriteSheetInfo) {
                os << spriteSheetInfo.noOfSprites << " " << spriteSheetInfo.gridSize.x << " " << spriteSheetInfo.gridSize.y << "\n";
                os << spriteSheetInfo.textureInfo;

                for (auto& e : spriteSheetInfo.animations) {
                    os << e.first << "\n";

                    for (auto& ee : e.second)
                        os << ee.first << ", " << ee.second << "\n";
                }

                for (auto& e : spriteSheetInfo.frameDescriptions)
                    os << e << " ";

                os << "\n";
                return os;
            }
        };

        void parseTexture(TextureInfo& textureInfo);

        void parseSpriteSize(int& noOfSprites, glm::ivec2& gridSize);

        void parseAnimationName(std::string& name);

        void parseKeyFrame(int& index, float& timeUntilNextFrame);

        void parseFrameDescription(std::string& frameDescription);

        void parseKeyFrames(std::ifstream& fin, std::vector<std::pair<int, float>>& keyFrames);

        void parseAnimation(std::ifstream& fin, std::vector<std::pair<std::string, std::vector<std::pair<int, float>>>>& animations);

        void parseAnimations(std::ifstream& fin, std::vector<std::pair<std::string, std::vector<std::pair<int, float>>>>& animations);

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
