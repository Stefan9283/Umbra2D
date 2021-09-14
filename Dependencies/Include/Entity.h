#pragma once

#include "Common.h"

namespace Umbra2D {
    class Entity {
     private:
        entt::registry *reg;
        entt::entity id;
     public:
        Entity(entt::registry* reg);
        ~Entity();

        uint32_t getID();

        template<typename T, typename... Args>
        void addComponent(Args... args) {
            reg->emplace<T>(id, std::forward<Args>(args)...);
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
        }

        void gui();
    };
}

