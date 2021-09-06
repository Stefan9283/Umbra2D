#include "AssetLibrary.h"
#include "Entity.h"
#include "Texture.h"
#include "Quad.h"

namespace Umbra2D {
    AssetLibrary::AssetLibrary() {
        q = new Quad();
    }
    void AssetLibrary::gui() {
        if (ImGui::TreeNode("AssetLibrary")) {
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
            ImGui::TreePop();
        }
    }
    // TODO
    unsigned int AssetLibrary::addSpriteSheet(std::string path, glm::vec2 gridSize, unsigned int numSprites) {
        unsigned int index = 0;
        for (auto ss : this->spriteSheets) {
            if (ss->tex->getPath() == path)
                return index;
            
        }
        this->spriteSheets.push_back(new Umbra2D::Assets::SpriteSheet(path, gridSize, numSprites));
        return index;
    }
    unsigned int AssetLibrary::addTexture(std::string path) {
        unsigned int index = 0;
        for (auto tex : this->textures) {
            if (tex->getPath() == path)
                return index;
        }
        this->textures.push_back(new Umbra2D::Assets::Texture(path));
        return index;
    }
}


