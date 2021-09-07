#pragma once

#include "Common.h"

constexpr auto MAX_LEN = 1024;

namespace Umbra2D {
    class Loader {
    private:
        std::string path;
        char buffer[MAX_LEN];

        struct TextureInfo {
            std::string name, path;

            /*friend std::ostream& operator<<(std::ostream& os, const TextureInfo& textureInfo) {
                os << textureInfo.name << " " << textureInfo.path << "\n";
                return os;
            }*/
        };

        struct SpriteSheetInfo {
            int noOfSprites;
            glm::ivec2 gridSize;
            TextureInfo textureInfo;

            std::vector<ANIMATION> animations;
            std::vector<std::string> frameDescriptions;

            /*friend std::ostream& operator<<(std::ostream& os, const SpriteSheetInfo& spriteSheetInfo) {
                os << spriteSheetInfo.noOfSprites << " " << spriteSheetInfo.textureInfo << "\n";
                os << spriteSheetInfo.gridSize.x << " " << spriteSheetInfo.gridSize.y << "\n";

                for (ANIMATION animation : spriteSheetInfo.animations) {
                    os << animation.name << "\n";

                    for (std::pair<int, float>& keyFrame : animation.frames)
                        os << keyFrame.first << ", " << keyFrame.second << "\n";
                }

                for (std::string frameDescription : spriteSheetInfo.frameDescriptions)
                    os << frameDescription << " ";

                os << "\n";
                return os;
            }*/
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
