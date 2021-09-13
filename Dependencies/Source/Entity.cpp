#include "Entity.h"
#include "AssetLibrary.h"
#include "Colliders.h"
#include "Shader.h"
#include "Texture.h"
#include "Quad.h"
#include "Engine.h"

extern Umbra2D::Engine* umbra;

long long unsigned int entitiesCount = 0;

namespace Umbra2D {
    glm::mat4 transform2D::toMat4() {
        return 
            glm::translate(glm::mat4(1), glm::vec3(this->translation.x, this->translation.y, 1)) *
            glm::toMat4(this->rotation) *
            glm::scale(glm::mat4(1), glm::vec3(this->scale.x, this->scale.y, 1));
    }
    void transform2D::gui(long long unsigned int id) {
        ImGui::SliderFloat2(std::string("translate ").append(std::to_string(id)).c_str(), (float*)&translation, -1000, 1000);
        if (ImGui::SliderFloat4(std::string("rotate ").append(std::to_string(id)).c_str(), (float*)&rotation, -1, 1))
            rotation = glm::normalize(rotation);
        ImGui::SliderFloat2(std::string("scale ").append(std::to_string(id)).c_str(), (float*)&scale, 1, 10000);
        ImGui::SliderInt(std::string("layer ").append(std::to_string(id)).c_str(), &layer, 1, 99);
    }
    void transform2D::rotate(float degrees) {
        rotation = glm::rotate(rotation, glm::radians(degrees), glm::vec3(0, 0, 1));
    }

    Entity::Entity() {
        id = entitiesCount;
        entitiesCount++;
    }
    void Entity::gui() {
        ImGui::SliderInt(std::string("Pixelation Level ").append(std::to_string(id)).c_str(), (int*)&pixelateLevel, 0, 1000);
        ImGui::Checkbox(std::string("Draw ").append(std::to_string(id)).c_str(), &render);
        transform.gui(id);
    }
    void Entity::setCollider(Colliders::AbstractCollider* c) {
        delete this->collider;
        this->collider = c;
    }
    Entity::~Entity() {
        delete this->collider;
    }

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
        Entity::gui();
        ImGui::SliderInt(("Current Sprite " + std::to_string(id)).c_str(), (int*)&currentSprite, 0, (int)ss->getSize().x - 1);
        ImGui::SliderFloat(("Animation Speed " + std::to_string(id)).c_str(), &animationSpeed, 0.f, 100.f);
        if (ImGui::SliderInt(("Playing Animation " + std::to_string(id)).c_str() , &animationPlaying, -1, ss->getAnimationsCount() - 1))
            setAnimation(animationPlaying);
        ImGui::Checkbox(("Loop Animation " + std::to_string(id)).c_str(), &loopAnimation);
        ss->gui();
    }
    void Dynamic::draw(Shader* s) {
        if (!render) return;

        glm::mat4 model = transform.toMat4();
        s->setMat4("model", &model);
        s->setInt("pixelateLevel", pixelateLevel);
        s->setFloat("depth", (const float)transform.layer);

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


    void Static::setTexture(std::string path, std::string name) {
        t = LIBRARY->textures[LIBRARY->addTexture(path, name)];
    }
    void Static::setTexture(TEXTURE* tex) {
        this->t = tex;
    }
    void Static::gui() {
        Entity::gui();
        t->gui();
    }
    void Static::draw(Shader* s) {
        if (!render) return;
        glm::mat4 model = transform.toMat4();
        s->setMat4("model", &model);
        s->setInt("pixelateLevel", pixelateLevel);
        s->setFloat("depth", (const float)transform.layer);
        s->setVec2("start", glm::vec2(0));
        s->setVec2("end", glm::vec2(1));
        if (t)
            s->setTexture("Texture", t->getID(), 0);
        else {
            s->setTexture("Texture", LIBRARY->defaultTexture->getID(), 0);
        }

        LIBRARY->q->draw();
    }
}
