#include "AssetLibrary.h"

#include <utility>
#include "Entity.h"
#include "Texture.h"
#include "Graphics/Quad.h"
#include "Graphics/Shader.h"

namespace Umbra2D {
    AssetLibrary::AssetLibrary() {
        defaultTexture = new TEXTURE("Dependencies/Assets/Textures/DefaultTexture.png", "DefaultTexture");
        q = new Umbra2D::Graphics::Quad();
        dq = new Umbra2D::Graphics::DynamicQuad();
    }
    AssetLibrary::~AssetLibrary() {
        for (auto* tex : textures)
            delete tex;
        for (auto spritesh : spriteSheets)
            delete spritesh;
        delete q;
        delete dq;
        delete defaultTexture;
    }

    void AssetLibrary::gui() {
        if (ImGui::Begin("Asset Library")) {
            if (ImGui::TreeNode(("Textures (" + std::to_string(this->textures.size()) + ")").c_str())) {
                for (auto t : this->textures)
                    t->gui();
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(("SpriteSheets (" + std::to_string(this->spriteSheets.size()) + ")").c_str())) {
                for (auto ss : this->spriteSheets)
                    ss->gui();
                ImGui::TreePop();
            }
            if (ImGui::TreeNode(("Shaders (" + std::to_string(this->shaders.size()) + ")").c_str())) {
                for (auto sh : this->shaders)
                    sh->gui();
                ImGui::TreePop();
            }
        }
        ImGui::End();
    }

    unsigned int AssetLibrary::addSpriteSheet(const std::string& path, glm::vec2 gridSize, unsigned int numSprites, std::string name) {
        unsigned int index = 0;
        for (auto ss : this->spriteSheets) {
            // TODO keep in mind that ./REL_PATH and REL_PATH are one and the same
            if (ss->tex->getPath() == path)
                return index;
            index++;
        }
        this->spriteSheets.push_back(new SPRITE_SHEET(path, gridSize, numSprites, std::move(name)));
        return index;
    }
    unsigned int AssetLibrary::addTexture(const std::string& path, std::string name) {
        unsigned int index = 0;
        for (auto tex : this->textures) {
            if (tex->getPath() == path)
                return index;
            index++;
        }
        this->textures.push_back(new TEXTURE(path, std::move(name)));
        return index;
    }

    unsigned int AssetLibrary::addShader(const std::string& name, const std::string &pathv, const std::string &pathf) {
        unsigned int index = 0;
        for (auto& sh : this->shaders) {
            auto paths = sh->getPaths();
            if (paths.first == pathv && paths.second == pathf)
                return index;
            index++;
        }
        this->shaders.push_back(new Umbra2D::Graphics::Shader(name, pathv, pathf));
        return index;
    }
}
