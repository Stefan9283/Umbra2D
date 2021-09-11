#pragma once

#include "Common.h"

namespace Umbra2D {
    class Shader;

    struct transform2D {
        glm::vec2 scale{1, 1}, translation{};
        glm::quat rotation = glm::quat(glm::vec3(0)); 
        int layer = 1; // it can be any value in [0, 1000]
        glm::mat4 toMat4();
        void gui(long long unsigned int id);
        // rotates around the Z axis
        void rotate(float degrees);
    };

    class Entity {
     private:
        Umbra2D::Colliders::AbstractCollider* collider = nullptr;
     public:
        long long unsigned int id;
        unsigned int pixelateLevel = 0;
        bool render = true;
        transform2D transform;

        void setCollider(Umbra2D::Colliders::AbstractCollider* c);
        Entity();
        ~Entity();

        virtual void gui();
        virtual void draw(Shader* s) = 0;
    };
    class Dynamic : public Entity {
        public:
        SPRITE_SHEET* ss = nullptr;
        int animationPlaying = -1;
        unsigned int currentSprite = 0;
        double time = 0;
        bool loopAnimation = false;
        float animationSpeed = 1;

        void setSpriteSheet(SPRITE_SHEET* ss);
        void setSpriteSheet(std::string pathToImage, glm::vec2 gridSize = glm::vec2(1),
                        unsigned int numOfSprites = 1, std::string name = "");
        void setAnimation(unsigned int animationID);

        void gui();
        void draw(Shader* s) override;
    };
    class Static : public Entity {
        public:
        TEXTURE* t = nullptr;

        void setTexture(std::string path, std::string name = "");
        void setTexture(TEXTURE* tex);

        void gui();
        void draw(Shader* s) override;
    };
}