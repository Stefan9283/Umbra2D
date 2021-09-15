#pragma once

#include "Common.h"
#include "Components/Component.h"

namespace Umbra2D {
    class Entity {
     private:
        std::string label;
        entt::registry *reg { nullptr };
        entt::entity id { entt::null };
     public:
        Entity(std::string label, entt::registry* reg);
        ~Entity();

        uint32_t getID();

        template<typename T, typename... Args>
        T* addComponent(Args... args) {
            std::cout << "Bruh\n";
            auto& comp = reg->emplace<T>(id, std::forward<Args>(args)...);
            ((COMPONENT*)&comp)->setParent(this);
            return &comp;
        }
        template<typename T>
        T* addComponent() {
            std::cout << "Bruh2\n";
            T& comp = reg->emplace<T>(id);
            ((COMPONENT*)&comp)->setParent(this);
            return &comp;
        }
//        template<typename T, typename S>
//        S* addComponent(S* comp) {
//            auto comp = reg->emplace<T*>(id, (T*)comp);
//            ((COMPONENT*)comp)->setParent(this);
//            return (S*)comp;
//        }
        template<typename T>
        bool hasComponent() {
            return reg->all_of<T>(id);
        }
//        template<typename T>
//        bool hasPointerComponent() {
//            return reg->all_of<T*>(id);
//        }

        template<typename T>
        T* getComponent() {
            return &reg->get<T>(id);
        }
//        template<typename T>
//        T* getPointerComponent() {
//            return reg->get<T*>(id);
//        }

        void gui();
    };
}

