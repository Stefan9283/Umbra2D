#pragma once

#include "Common.h"
#include "Components/Component.h"
#include "Scene.h"

#include "Engines/Engine.h"
#include "Gui/Logger.h"

extern Umbra2D::Umbra2DEngine *umbra;

namespace Umbra2D {
    class Entity {
     private:
        std::string label = "";
        Umbra2D::Scene* scene { nullptr };
        entt::entity id { entt::null };
     public:
        Entity(std::string label, Umbra2D::Scene* s);
        ~Entity();

        uint32_t getID();

        template<typename T, typename... Args>
        T* addComponent(Args... args) {
            if (!hasComponent<T>()) {
                auto &comp = scene->registry.emplace<T>(id, std::forward<Args>(args)...);
                ((COMPONENT *) &comp)->setParent(this);
                return &comp;
            } else {
                umbra->logger->addLog("warning",
                          std::string("Component of type ")
                          .append(typeid(T).name())
                          .append(" already exists for entity ")
                          .append(label)
                          .append(" (id ")
                          .append(std::to_string(getID()))
                          .append(")"));
                return getComponent<T>();
            }
        }
        template<typename T>
        T* addComponent() {
            if (!hasComponent<T>()) {
                T &comp = scene->registry.emplace<T>(id);
                ((COMPONENT *) &comp)->setParent(this);
                return &comp;
            } else {
                umbra->logger->addLog("warning",
                        std::string("Component of type ")
                        .append(typeid(T).name())
                        .append(" already exists for entity ")
                        .append(label)
                        .append(" (id ")
                        .append(std::to_string(getID()))
                        .append(")"));
                return getComponent<T>();
            }
        }
//        template<typename T, typename S>
//        S* addComponent(S* comp) {
//            auto comp = scene->registry.emplace<T*>(id, (T*)comp);
//            ((COMPONENT*)comp)->setParent(this);
//            return (S*)comp;
//        }

        template<typename T>
        bool hasComponent() {
            return scene->registry.all_of<T>(id);
        }
//        template<typename T>
//        bool hasPointerComponent() {
//            return scene->registry.all_of<T*>(id);
//        }



        template<typename T>
        T* getComponent() {
            if (hasComponent<T>())
                return &scene->registry.get<T>(id);
            return nullptr;
        }
//        template<typename T>
//        T* getPointerComponent() {
//            return scene->registry.get<T*>(id);
//        }

        void gui();
    };
}

