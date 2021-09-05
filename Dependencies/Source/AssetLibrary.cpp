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
            if (ImGui::TreeNode("Textures")) {
                for (auto t : this->textures)
                    t->gui();
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("SpriteSheets")) {
                for (auto ss : this->spriteSheets)
                    ss->gui();
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }
    unsigned int AssetLibrary::addSpriteSheet(std::string path, glm::vec2 gridSize, unsigned int numSprites) {
        unsigned int index = 0;
        for (auto ss : this->spriteSheets) {
            if (ss->tex->path == path)
                return index;
            
        }
        this->spriteSheets.push_back(new Umbra2D::Assets::SpriteSheet(path, gridSize, numSprites));
        return index;
    }
    unsigned int AssetLibrary::addTexture(std::string path) {
        unsigned int index = 0;
        for (auto tex : this->textures) {
            if (tex->path == path)
                return index;
        }
        this->textures.push_back(new Umbra2D::Assets::Texture(path));
        return index;
    }
}


