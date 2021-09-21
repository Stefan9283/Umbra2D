#include "Umbra2D.h"

extern Umbra2D::Umbra2DEngine* umbra;

namespace Umbra2D::Components::Renderables {
    void Dynamic::setSpriteSheet(SPRITE_SHEET* spriteSheet) {
        this->ss = spriteSheet;
    }
    void Dynamic::setSpriteSheet(const std::string& pathToImage, glm::vec2 gridSize, unsigned int numOfSprites, std::string name) {
        ss = LIBRARY->spriteSheets[LIBRARY->addSpriteSheet(pathToImage, gridSize, numOfSprites, std::move(name))];
    }
    void Dynamic::setAnimation(int animationID) {
        time = glfwGetTime();
        animationPlaying = animationID;
    }
    void Dynamic::gui() {
        std::string parentID = std::to_string(this->getParent()->getID());
        if (ImGui::TreeNode(("Dynamic " + parentID).c_str())) {
            ImGui::Text("Dynamic %s", parentID.c_str());


            std::string texName;
            if (ss) {
                texName = ss->tex->name;
                ImGui::SliderInt(("Current Sprite " + parentID).c_str(), (int *) &currentSprite, 0, (int) ss->getSize().x - 1);
                if (ImGui::SliderInt(("Playing Animation " + parentID).c_str(), &animationPlaying, -1, ss->getAnimationsCount() - 1))
                    setAnimation(animationPlaying);
                ss->gui();
            } else {
                texName = "No Sprite Sheet has been set";
            }

            ImGui::Text("%s", texName.c_str());
            if (ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("TEXTURE_PATH")) {
                    setSpriteSheet(std::string((char*)payload->Data));
                }
                ImGui::EndDragDropTarget();
            }

            ImGui::SliderFloat(("Animation Speed " + parentID).c_str(), &animationSpeed, 0.f, 100.f);
            ImGui::Checkbox(("Loop Animation " + parentID).c_str(), &loopAnimation);
            ImGui::TreePop();
        }
    }
    void Dynamic::draw(Umbra2D::Graphics::Shader* s) {
        if (!render) return;
        glm::mat4 model = getParent()->hasComponent<TRANSFORM>() ? getParent()->getComponent<TRANSFORM>()->toMat4() : glm::mat4(1);
        s->setMat4("model", &model);
//        s->setInt("pixelateLevel", pixelateLevel);
//        s->setFloat("depth", (const float)transform.layer);
        if (animationPlaying == -1) {
            if (ss) {
                auto coords = ss->getSpriteCell(currentSprite);
                s->setVec2("start", coords.first);
                s->setVec2("end", coords.second);
                s->setTexture("Texture", ss->tex->getID(), 0);
            } else {
                s->setVec2("start", glm::vec2(0));
                s->setVec2("end", glm::vec2(1));
                s->setTexture("Texture", LIBRARY->defaultTexture->getID(), 0);
            }
        } else {
            if (ss) {
                float delta = (float)(glfwGetTime() - time);
                delta *= animationSpeed;
                ANIMATION anim = ss->getAnimation(animationPlaying);
                auto closestIndex = anim.getBestFrameInterval(delta);
                auto coords = ss->getSpriteCell(closestIndex);
                s->setVec2("start", coords.first);
                s->setVec2("end", coords.second);
                s->setTexture("Texture", ss->tex->getID(), 0);
                if (loopAnimation && anim.getTotalDuration() < delta)
                    time = glfwGetTime();
            } else {
                s->setVec2("start", glm::vec2(0));
                s->setVec2("end", glm::vec2(1));
                s->setTexture("Texture", LIBRARY->defaultTexture->getID(), 0);
            }
        }

        LIBRARY->q->draw();
    }

    void Static::setTexture(const std::string& path, std::string name) {
        t = LIBRARY->textures[LIBRARY->addTexture(path, std::move(name))];
    }
    void Static::setTexture(TEXTURE* tex) {
        this->t = tex;
    }
    void Static::gui() {
        if (ImGui::TreeNode(("Static " + std::to_string(getParent()->getID())).c_str())) {

            std::string texName;
            if (t) {
                texName = t->name;
            } else {
                texName = "No Texture has been set";
            }

            ImGui::Text("%s", texName.c_str());
            if (ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("TEXTURE_PATH")) {
                    setTexture(std::string((char*)payload->Data));
                }
                ImGui::EndDragDropTarget();
            }

            if (t) t->gui();
            ImGui::TreePop();
        }
    }
    void Static::draw(Umbra2D::Graphics::Shader* s) {
        if (!render) return;
        glm::mat4 model = getParent()->hasComponent<TRANSFORM>() ? getParent()->getComponent<TRANSFORM>()->toMat4() : glm::mat4(1);
        s->setMat4("model", &model);
//        s->setInt("pixelateLevel", pixelateLevel);
//        s->setFloat("depth", (const float)transform.layer);
        s->setVec2("start", glm::vec2(0));
        s->setVec2("end", glm::vec2(1));

        if (t) {
            s->setTexture("Texture", t->getID(), 0);
        } else {
            s->setTexture("Texture", LIBRARY->defaultTexture->getID(), 0);
        }

        LIBRARY->q->draw();
    }
}