#pragma once

#include "Common.h"

namespace Umbra2D {
    class Texture;
    class SpriteSheet;
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
     public:
        long long unsigned int id;
        unsigned int pixelateLevel = 0;
        transform2D transform;
        bool render = true;
        Entity();
        virtual void draw(Shader* s) = 0;
        void gui();
    };
    class Actor : public Entity {
        public:
        SpriteSheet* ss;
        void draw(Shader* s) override;
    };
    class Decor : public Entity {
        public:
        Texture* t;
        void draw(Shader* s) override;
    };
}