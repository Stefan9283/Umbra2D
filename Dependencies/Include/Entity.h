#pragma once

#include "Common.h"
#include "Components/Component.h"

namespace Umbra2D {
    class Entity {
     private:
        std::string label;
        Umbra2D::Scene* scene { nullptr };
        entt::entity id { entt::null };
     public:
        Entity(std::string label, Umbra2D::Scene* s);
        ~Entity();

        uint32_t getID();

        template<typename T, typename... Args>
        T* addComponent(Args... args);

        template<typename T>
        T* addComponent();

//        template<typename T, typename S>
//        S* addComponent(S* comp) {
//            auto comp = scene->registry.emplace<T*>(id, (T*)comp);
//            ((COMPONENT*)comp)->setParent(this);
//            return (S*)comp;
//        }


        template<typename T>
        bool hasComponent();
//        template<typename T>
//        bool hasPointerComponent() {
//            return scene->registry.all_of<T*>(id);
//        }



        template<typename T>
        T* getComponent();
//        template<typename T>
//        T* getPointerComponent() {
//            return scene->registry.get<T*>(id);
//        }

        void gui();
    };
}

