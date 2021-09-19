#include "IO/Saver.h"
#include "Texture.h"
#include "AssetLibrary.h"
#include "Graphics/Shader.h"
#include "Engines/Engine.h"

extern Umbra2D::Umbra2DEngine* umbra;

namespace Umbra2D::IO {
    void Saver::saveTexture(std::ofstream& fout, TEXTURE* texture, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "Texture[" << texture->name << ", " << texture->getPath() << "]\n";
    }

    void Saver::saveSpriteSize(std::ofstream& fout, SPRITE_SHEET* spriteSheet, int depth) {
        glm::vec3 size = spriteSheet->getSize();

        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "SpriteSize[" << size.x << ", " << size.y << ", " << size.z << "]\n";
    }

    void Saver::saveFrameDescription(std::ofstream& fout, std::string& description, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "FrameDescription[" << description << "]\n";
    }

    void Saver::saveAnimationName(std::ofstream& fout, std::string& name, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "AnimationName[" << name << "]\n";
    }

    void Saver::saveKeyFrame(std::ofstream& fout, std::pair<int, float>& keyFrame, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "KeyFrame[" << keyFrame.first << ", " << keyFrame.second << "]\n";
    }

    void Saver::saveShader(std::ofstream& fout, SHADER* shader, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        auto paths = shader->getPaths();

        fout << "Shader[" << shader->getName() << ", " << paths.first << ", " << paths.second << "]\n";
    }

    void Saver::saveKeyFrames(std::ofstream& fout, std::vector<std::pair<int, float>>& keyFrames, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "KeyFrames[\n";

        for (std::pair<int, float>& keyFrame : keyFrames)
            saveKeyFrame(fout, keyFrame, depth + 1);

        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "]\n";
    }

    void Saver::saveAnimation(std::ofstream& fout, ANIMATION& animation, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "Animation[\n";
        saveAnimationName(fout, animation.name, depth + 1);
        saveKeyFrames(fout, animation.frames, depth + 1);

        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "]\n";
    }

    void Saver::saveAnimations(std::ofstream& fout, SPRITE_SHEET* spriteSheet, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "Animations[\n";

        for (ANIMATION& animation : spriteSheet->getAnimations())
            saveAnimation(fout, animation, depth + 1);

        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "]\n";
    }

    void Saver::saveFrameDescriptions(std::ofstream& fout, SPRITE_SHEET* spriteSheet, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "FrameDescriptions[\n";

        for (std::string& frameDescription : spriteSheet->getFrameDescriptions())
            saveFrameDescription(fout, frameDescription, depth + 1);

        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "]\n";
    }

    void Saver::saveSpriteSheet(std::ofstream& fout, SPRITE_SHEET* spriteSheet, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "SpriteSheet[\n";
        saveSpriteSize(fout, spriteSheet, depth + 1);
        saveTexture(fout, spriteSheet->tex, depth + 1);
        saveAnimations(fout, spriteSheet, depth + 1);
        saveFrameDescriptions(fout, spriteSheet, depth + 1);

        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "]\n";
    }

    void Saver::saveTextures(std::ofstream& fout, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "Textures[\n";

        for (TEXTURE* texture : LIBRARY->textures)
            saveTexture(fout, texture, depth + 1);

        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "]\n";
    }

    void Saver::saveSpriteSheets(std::ofstream& fout, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "SpriteSheets[\n";

        for (SPRITE_SHEET* spriteSheet : LIBRARY->spriteSheets)
            saveSpriteSheet(fout, spriteSheet, depth + 1);

        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "]\n";
    }

    void Saver::saveShaders(std::ofstream& fout, int depth) {
        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "Shaders[\n";

        for (SHADER* shader : LIBRARY->shaders)
            saveShader(fout, shader, depth + 1);

        for (int i = 0; i < depth; i++)
            fout << "\t";

        fout << "]\n";
    }

    void Saver::saveAssetLibrary(std::ofstream& fout, int depth) {
        fout << "AssetLibrary[\n";
        saveTextures(fout, depth + 1);
        fout << "\n";
        saveSpriteSheets(fout, depth + 1);
        fout << "\n";
        saveShaders(fout, depth + 1);
        fout << "]\n";
    }

    Saver::Saver(std::string path) {
        this->path = path;
    }

    void Saver::saveSettings() {
        std::ofstream fout(path);

        saveAssetLibrary(fout, 0);
        fout.close();
    }
}
