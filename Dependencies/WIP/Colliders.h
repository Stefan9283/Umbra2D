#pragma once

#include "Common.h"

namespace Umbra2D {
    class Rectangle;
    class Circle;
    class Line;

    class Collider {
        public:
        virtual bool checkCollision(Rectangle* c) = 0;
        virtual bool checkCollision(Circle* c) = 0;
        virtual bool checkCollision(Line* c) = 0;
    };
    
    class Rectangle : Collider {
        public:
        glm::vec2 min, max;
        bool checkCollision(Rectangle* c) override;
        bool checkCollision(Circle* c) override;
        bool checkCollision(Line* c) override;
    };
    
    class Circle : Collider {
        public:
        float radius;
        glm::vec2 pos;
        bool checkCollision(Rectangle* c) override;
        bool checkCollision(Circle* c) override;
        bool checkCollision(Line* c) override;
    };
    
    class Line : Collider {
        public:
        float length;
        glm::vec2 pos, direction;
        bool checkCollision(Rectangle* c) override;
        bool checkCollision(Circle* c) override;
        bool checkCollision(Line* c) override;
    };
}

