#include "Components/Renderable.h"
#include "Engines/Engine.h"
#include "AssetLibrary.h"
#include "Texture.h"
#include "Entity.h"

extern Umbra2D::Engine* umbra;

namespace Umbra2D::Components::Renderables {
    void Dynamic::setSpriteSheet(SPRITE_SHEET* ss) {
        this->ss = ss;
    }
    void Dynamic::setSpriteSheet(std::string pathToImage, glm::vec2 gridSize, unsigned int numOfSprites, std::string name) {
        ss = LIBRARY->spriteSheets[LIBRARY->addSpriteSheet(pathToImage, gridSize, numOfSprites, name)];
    }
    void Dynamic::setAnimation(unsigned int animationID) {
        time = glfwGetTime();
        animationPlaying = animationID;
    }
    void Dynamic::gui() {
        ImGui::Text("%d", this->getParent()->getID());
//        ImGui::SliderInt(("Current Sprite " + std::to_string(id)).c_str(), (int*)&currentSprite, 0, (int)ss->getSize().x - 1);
//        ImGui::SliderFloat(("Animation Speed " + std::to_string(id)).c_str(), &animationSpeed, 0.f, 100.f);
//        if (ImGui::SliderInt(("Playing Animation " + std::to_string(id)).c_str() , &animationPlaying, -1, ss->getAnimationsCount() - 1))
//            setAnimation(animationPlaying);
//        ImGui::Checkbox(("Loop Animation " + std::to_string(id)).c_str(), &loopAnimation);
        ss->gui();
    }
//    void Dynamic::draw(Shader* s) {
//        if (!render) return;
//
//        glm::mat4 model = transform.toMat4();
//        s->setMat4("model", &model);
//        s->setInt("pixelateLevel", pixelateLevel);
//        s->setFloat("depth", (const float)transform.layer);
//
//        if (animationPlaying == -1) {
//            if (ss) {
//                auto coords = ss->getSpriteCell(currentSprite);
//                s->setVec2("start", coords.first);
//                s->setVec2("end", coords.second);
//                s->setTexture("Texture", ss->tex->getID(), 0);
//            } else {
//                s->setVec2("start", glm::vec2(0));
//                s->setVec2("end", glm::vec2(1));
//                s->setTexture("Texture", LIBRARY->defaultTexture->getID(), 0);
//            }
//        } else {
//            if (ss) {
//                float delta = (float)(glfwGetTime() - time);
//                delta *= animationSpeed;
//                ANIMATION anim = ss->getAnimation(animationPlaying);
//                auto closestIndex = anim.getBestFrameInterval(delta);
//                auto coords = ss->getSpriteCell(closestIndex);
//                s->setVec2("start", coords.first);
//                s->setVec2("end", coords.second);
//                s->setTexture("Texture", ss->tex->getID(), 0);
//                if (loopAnimation && anim.getTotalDuration() < delta)
//                    time = glfwGetTime();
//            } else {
//                s->setVec2("start", glm::vec2(0));
//                s->setVec2("end", glm::vec2(1));
//                s->setTexture("Texture", LIBRARY->defaultTexture->getID(), 0);
//            }
//        }
//
//        LIBRARY->q->draw();
//    }
//
//
    void Static::setTexture(std::string path, std::string name) {
        t = LIBRARY->textures[LIBRARY->addTexture(path, name)];
    }
    void Static::setTexture(TEXTURE* tex) {
        this->t = tex;
    }
    void Static::gui() {
//        Entity::gui();
        t->gui();
    }
//    void Static::draw(Shader* s) {
//        if (!render) return;
//        glm::mat4 model = transform.toMat4();
//        s->setMat4("model", &model);
//        s->setInt("pixelateLevel", pixelateLevel);
//        s->setFloat("depth", (const float)transform.layer);
//        s->setVec2("start", glm::vec2(0));
//        s->setVec2("end", glm::vec2(1));
//        if (t)
//            s->setTexture("Texture", t->getID(), 0);
//        else {
//            s->setTexture("Texture", LIBRARY->defaultTexture->getID(), 0);
//        }
//
//        LIBRARY->q->draw();
//    }
}