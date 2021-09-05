#pragma once

#include "Common.h"

namespace Umbra2D {
    class Rectangle;
    class Circle;
    class Line;

    class Collider {
        public:
        glm::vec2 pos;
        virtual bool checkCollision(Rectangle* c) = 0;
        virtual bool checkCollision(Circle* c) = 0;
        virtual bool checkCollision(Line* c) = 0;
        virtual void draw() = 0;
        virtual void gui() = 0;
    };
    
    class Rectangle : public Collider {
        public:
        glm::vec2 dimensions;
        bool checkCollision(Rectangle* c) override;
        bool checkCollision(Circle* c) override;
        bool checkCollision(Line* c) override;
        void draw() override;
        void gui() override;
    };
    
    class Circle : public Collider {
        public:
        float radius;
        bool checkCollision(Rectangle* c) override;
        bool checkCollision(Circle* c) override;
        bool checkCollision(Line* c) override;
        void draw() override;
        void gui() override;
    };
    
    class Line : public Collider {
        public:
        float length;
        glm::vec2 direction;
        bool checkCollision(Rectangle* c) override;
        bool checkCollision(Circle* c) override;
        bool checkCollision(Line* c) override;
        void draw() override;
        void gui() override;
    };
}

