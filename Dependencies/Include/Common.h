#pragma once

/*
 *  add any STL or external lib header reference here  
*/

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

//#include <ft2build.h>
//#include FT_FREETYPE_H

#include <stb_image.h>

#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>

constexpr auto MAX_LEN = 1024;

namespace Umbra2D {
    class Loader;
    class AssetLibrary;

    /*class Loader {
    private:
        std::string path;
        AssetLibrary* lib;

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

        void parseTexture(TextureInfo& textureInfo) {
            int i = 0, j;

            for (i; i < strlen(buffer); i++)
                if (buffer[i] == '[')
                    break;

            for (j = i + 1; j < strlen(buffer); j++)
                if (buffer[j] == ',')
                    break;

            textureInfo.name = std::string(buffer + i + 1, buffer + j);
            textureInfo.path = std::string(buffer + j + 1, buffer + strlen(buffer) - 1);
        }

        void parseSpriteSize(int& noOfSprites, glm::ivec2& gridSize) {
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
            gridSize = {atoi(std::string(buffer + j + 1, buffer + k).c_str()),
                        atoi(std::string(buffer + k + 1, buffer + strlen(buffer) - 1).c_str())};
        }

        void parseAnimationName(std::string& name) {
            int i;

            for (i = 0; i < strlen(buffer); i++)
                if (buffer[i] == '[')
                    break;

            name = std::string(buffer + i + 1, buffer + strlen(buffer) - 1);
        }

        void parseKeyFrame(int& index, float& timeUntilNextFrame) {
            int i = 0, j;

            for (i; i < strlen(buffer); i++)
                if (buffer[i] == '[')
                    break;

            for (j = i + 1; j < strlen(buffer); j++)
                if (buffer[j] == ',')
                    break;

            index = atoi(std::string(buffer + i + 1, buffer + j).c_str());
            timeUntilNextFrame = std::stof(std::string(buffer + j + 1, buffer + strlen(buffer) - 1));
        }

        void parseFrameDescription(std::string& frameDescription) {
            int i;

            for (i = 0; i < strlen(buffer); i++)
                if (buffer[i] == '[')
                    break;

            frameDescription = std::string(buffer + i + 1, buffer + strlen(buffer) - 1);
        }

        void parseKeyFrames(std::ifstream& fin, std::vector<std::pair<int, float>>& keyFrames) {
            while (fin.getline(buffer, MAX_LEN))
                if (strstr(buffer, "KeyFrame")) {
                    int index;
                    float timeUntilNextFrame;

                    parseKeyFrame(index, timeUntilNextFrame);
                    keyFrames.push_back({index, timeUntilNextFrame});
                } else
                    break;
        }

        void parseAnimation(std::ifstream& fin, std::vector<std::pair<std::string, std::vector<std::pair<int, float>>>>& animations) {
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

        void parseAnimations(std::ifstream& fin, std::vector<std::pair<std::string, std::vector<std::pair<int, float>>>>& animations) {
            while (fin.getline(buffer, MAX_LEN))
                if (strstr(buffer, "Animation"))
                    parseAnimation(fin, animations);
                else
                    break;
        }

        void parseFrameDescriptions(std::ifstream& fin, std::vector<std::string>& frameDescriptions) {
            while (fin.getline(buffer, MAX_LEN))
                if (strstr(buffer, "FrameDescription")) {
                    std::string frameDesctiption;

                    parseFrameDescription(frameDesctiption);
                    frameDescriptions.push_back(frameDesctiption);
                } else
                    break;
        }

        void parseSpriteSheet(std::ifstream& fin, SpriteSheetInfo& spriteSheetInfo) {
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

        void parseTextures(std::ifstream& fin) {
            while (fin.getline(buffer, MAX_LEN)) {
                if (strstr(buffer, "Texture")) {
                    TextureInfo textureInfo;

                    parseTexture(textureInfo);
                    lib->addTexture(textureInfo.path);
                } else
                    break;
            }
        }

        void parseSpriteSheets(std::ifstream& fin) {
            while (fin.getline(buffer, MAX_LEN))
                if (strstr(buffer, "SpriteSheet")) {
                    SpriteSheetInfo spriteSheetInfo;

                    parseSpriteSheet(fin, spriteSheetInfo);
                } else if (strlen(buffer) > 0)
                    break;

        }

        void parseAssetLibrary(std::ifstream& fin) {
            while (fin.getline(buffer, MAX_LEN))
                if (strstr(buffer, "Textures"))
                    parseTextures(fin);
                else if (strstr(buffer, "SpriteSheets"))
                    parseSpriteSheets(fin);
                else if (strlen(buffer) > 0)
                    break;
        }

    public:
        Loader(AssetLibrary* lib, std::string path) {
            this->lib = lib; this->path = path;
        }

        void parseInputFile() {
            std::ifstream fin(path);

            while (fin.getline(buffer, MAX_LEN))
                if (strstr(buffer, "AssetLibrary"))
                    parseAssetLibrary(fin);
                else
                    break;
 
            fin.close();
        }
    };*/

    namespace Assets {
        class Texture;    
        class SpriteSheet;
    }    

    class Camera;
    class Window;
    class Shader;
    class Quad;

    namespace Colliders {
        class AbstractCollider;
        class Rectangle;
        class Circle;
        class Line;
    }

    // entity types
    class Entity;
    class Static;
    class Dynamic;
}