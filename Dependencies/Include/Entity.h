#pragma once

#include "Common.h"

namespace Umbra2D {
    class Entity {
     private:
     public:
        entt::entity id;
        entt::registry *reg;
        Entity(entt::registry* reg);
        ~Entity();

        template<typename T, typename... Args>
        void addComponent(Args... args);

        template<typename T>
        bool hasComponent();

        template<typename T>
        T* getComponent();
    };
}