#include "Loader.h"
#include "Texture.h"
#include "AssetLibrary.h"
#include "Engine.h"

extern Umbra2D::Engine* umbra;

namespace Umbra2D {
    void Loader::parseTexture(TextureInfo& textureInfo) {
        int i = 0, j;
    
        for (i; i < strlen(buffer); i++)
            if (buffer[i] == '[')
                break;
    
        for (j = i + 1; j < strlen(buffer); j++)
            if (buffer[j] == ',')
                break;
    
        textureInfo.name = std::string(buffer + i + 1, buffer + j);
        textureInfo.path = std::string(buffer + j + 2, buffer + strlen(buffer) - 1);
    }
    
    void Loader::parseSpriteSize(int& noOfSprites, glm::ivec2& gridSize) {
        int i = 0, j, k;
    
        for (i; i < strlen(buffer); i++)
            if (buffer[i] == '[')
                break;
    
        for (j = i + 1; j < strlen(buffer); j++)
            if (buffer[j] == ',')
                break;
    
        for (k = j + 1; k < strlen(buffer); k++)
            if (buffer[k] == ',')
                break;
    
        noOfSprites = atoi(std::string(buffer + i + 1, buffer + j).c_str());
        gridSize = { atoi(std::string(buffer + j + 2, buffer + k).c_str()),
                    atoi(std::string(buffer + k + 2, buffer + strlen(buffer) - 1).c_str()) };
    }
    
    void Loader::parseAnimationName(std::string& name) {
        int i;
    
        for (i = 0; i < strlen(buffer); i++)
            if (buffer[i] == '[')
                break;
    
        name = std::string(buffer + i + 1, buffer + strlen(buffer) - 1);
    }
    
    void Loader::parseKeyFrame(int& index, float& timeUntilNextFrame) {
        int i = 0, j;
    
        for (i; i < strlen(buffer); i++)
            if (buffer[i] == '[')
                break;
    
        for (j = i + 1; j < strlen(buffer); j++)
            if (buffer[j] == ',')
                break;
    
        index = atoi(std::string(buffer + i + 1, buffer + j).c_str());
        timeUntilNextFrame = std::stof(std::string(buffer + j + 2, buffer + strlen(buffer) - 1));
    }
    
    void Loader::parseFrameDescription(std::string& frameDescription) {
        int i;
    
        for (i = 0; i < strlen(buffer); i++)
            if (buffer[i] == '[')
                break;
    
        frameDescription = std::string(buffer + i + 1, buffer + strlen(buffer) - 1);
    }
    
    void Loader::parseKeyFrames(std::ifstream& fin, std::vector<std::pair<int, float>>& keyFrames) {
        while (fin.getline(buffer, MAX_LEN))
            if (strstr(buffer, "KeyFrame")) {
                int index;
                float timeUntilNextFrame;
    
                parseKeyFrame(index, timeUntilNextFrame);
                keyFrames.push_back({index, timeUntilNextFrame});
            } else
                break;
    }
    
    void Loader::parseAnimation(std::ifstream& fin, std::vector<ANIMATION>& animations) {
        std::string name;
        std::vector<std::pair<int, float>> keyFrames;
    
        while (fin.getline(buffer, MAX_LEN))
            if (strstr(buffer, "AnimationName"))
                parseAnimationName(name);
            else if (strstr(buffer, "KeyFrames"))
                parseKeyFrames(fin, keyFrames);
            else
                break;
    
        animations.push_back({name, keyFrames});
    }
    
    void Loader::parseAnimations(std::ifstream& fin, std::vector<ANIMATION>& animations) {
        while (fin.getline(buffer, MAX_LEN))
            if (strstr(buffer, "Animation"))
                parseAnimation(fin, animations);
            else
                break;
    }
    
    void Loader::parseFrameDescriptions(std::ifstream& fin, std::vector<std::string>& frameDescriptions) {
        while (fin.getline(buffer, MAX_LEN))
            if (strstr(buffer, "FrameDescription")) {
                std::string frameDesctiption;
    
                parseFrameDescription(frameDesctiption);
                frameDescriptions.push_back(frameDesctiption);
            } else
                break;
    }
    
    void Loader::parseSpriteSheet(std::ifstream& fin, SpriteSheetInfo& spriteSheetInfo) {
        while (fin.getline(buffer, MAX_LEN))
            if (strstr(buffer, "SpriteSize"))
                parseSpriteSize(spriteSheetInfo.noOfSprites, spriteSheetInfo.gridSize);
            else if (strstr(buffer, "Texture"))
                parseTexture(spriteSheetInfo.textureInfo);
            else if (strstr(buffer, "Animations"))
                parseAnimations(fin, spriteSheetInfo.animations);
            else if (strstr(buffer, "FrameDescriptions"))
                parseFrameDescriptions(fin, spriteSheetInfo.frameDescriptions);
            else
                break;
    }
    
    void Loader::parseTextures(std::ifstream& fin) {
        while (fin.getline(buffer, MAX_LEN)) {
            if (strstr(buffer, "Texture")) {
                TextureInfo textureInfo;

                parseTexture(textureInfo);
                LIBRARY->addTexture(textureInfo.path, textureInfo.name);
            } else
                break;
        }
    }
    
    void Loader::parseSpriteSheets(std::ifstream& fin) {
        while (fin.getline(buffer, MAX_LEN))
            if (strstr(buffer, "SpriteSheet")) {
                SpriteSheetInfo spriteSheetInfo;
                unsigned int index;

                parseSpriteSheet(fin, spriteSheetInfo);
                index = LIBRARY->addSpriteSheet(spriteSheetInfo.textureInfo.path, spriteSheetInfo.gridSize,
                                            spriteSheetInfo.noOfSprites, spriteSheetInfo.textureInfo.name);

                for (int i = 0; i < spriteSheetInfo.frameDescriptions.size(); i++)
                    LIBRARY->spriteSheets[index]->addSpriteDescription(spriteSheetInfo.frameDescriptions[i], i);

                for (ANIMATION& animation : spriteSheetInfo.animations)
                    LIBRARY->spriteSheets[index]->addAnimation(animation);
            } else if (strlen(buffer) > 0)
                break;
    }
    
    void Loader::parseAssetLibrary(std::ifstream& fin) {
        while (fin.getline(buffer, MAX_LEN))
            if (strstr(buffer, "Textures"))
                parseTextures(fin);
            else if (strstr(buffer, "SpriteSheets"))
                parseSpriteSheets(fin);
            else if (strlen(buffer) > 0)
                break;
    }
    
    Loader::Loader(std::string path) {
        this->path = path;
    }
    
    void Loader::parseInputFile() {
        std::ifstream fin(path);
    
        while (fin.getline(buffer, MAX_LEN))
            if (strstr(buffer, "AssetLibrary"))
                parseAssetLibrary(fin);
            else
                break;
    
        fin.close();
    }
}
