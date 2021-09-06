#pragma once

#include "Common.h"

namespace Umbra2D {
    class Shader;

    struct transform2D {
        glm::vec2 scale{1, 1}, translation{};
        glm::quat rotation = glm::quat(glm::vec3(0)); 
        int layer = 1; // it can be any value in [1, 99]
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
        virtual void draw(Shader* s) = 0;
        void gui();
    };
    class Dynamic : public Entity {
        public:
        Umbra2D::Assets::SpriteSheet* ss;
        int animationPlaying;
        double time;

        void draw(Shader* s) override;
    };
    class Static : public Entity {
        public:
        Umbra2D::Assets::Texture* t;
        void setTexture(std::string path);
        void draw(Shader* s) override;
    };
}