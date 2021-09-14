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
        void addComponent(Args... args) {
            reg->emplace<T>(id, args);
        }
        template<typename T>
        void addComponent() {
            reg->emplace<T>(id);
        }
        template<typename T>
        bool hasComponent() {
            return reg->all_of<T>(id);
        }
        template<typename T>
        T* getComponent() {
            return &reg->get<T>(id);
//            return nullptr;
        }
    };
}

