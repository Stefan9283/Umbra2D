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
            // TODO
            ImGui::TreePop();
        }
    }
    void AssetLibrary::addSpriteSheet(std::string path, glm::vec2 gridSize, unsigned int numSprites) {
        this->spriteSheets.push_back(new SpriteSheet(path, gridSize, numSprites));
    }
    void AssetLibrary::addTexture(std::string path) {
        this->textures.push_back(new Texture(path));
    }
}


