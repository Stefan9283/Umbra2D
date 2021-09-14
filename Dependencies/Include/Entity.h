#pragma once

#include "Common.h"

namespace Umbra2D {
    class Entity {
     private:
        std::vector<Components::Component*> components;
//        Umbra2D::Colliders::AbstractCollider* collider = nullptr;
     public:
        long long unsigned int id;
//        unsigned int pixelateLevel = 0;
//        bool render = true;
//        transform2D transform;

//        void setCollider(Umbra2D::Colliders::AbstractCollider* c);
        Entity();
        ~Entity();
        void addComponent(Components::Component* c);
        void gui();
//        virtual void draw(Shader* s) = 0;
    };

//    class Dynamic : public Entity {
//        public:
//        void draw(Shader* s) override;
//    };
//    class Static : public Entity {
//        public:
//        void draw(Shader* s) override;
//    };
}