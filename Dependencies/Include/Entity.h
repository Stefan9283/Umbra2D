#pragma once

#include "Common.h"

namespace Umbra2D {
    class Entity {
     private:
     public:
        long long unsigned int id;
        Entity();
        ~Entity();

        template<typename T>
        void addComponent(Components::Component* c);

        template<typename T>
        bool hasComponent();

        template<typename T>
        T* getComponent();
    };
}