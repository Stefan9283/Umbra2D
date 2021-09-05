#pragma once

#include "Common.h"

namespace Umbra2D::Colliders {
    class AbstractCollider {
        public:
        glm::vec2 pos;
        virtual bool checkCollision(Rectangle* c) = 0;
        virtual bool checkCollision(Circle* c) = 0;
        virtual bool checkCollision(Line* c) = 0;
        // virtual void draw() = 0;
        // virtual void gui() = 0;
        virtual ~AbstractCollider() = default;
    };
    
    class Rectangle : public AbstractCollider {
        public:
        glm::vec2 dimensions;
        Rectangle(float height, float length, glm::vec2 center = {});
        bool checkCollision(Rectangle* c) override;
        bool checkCollision(Circle* c) override;
        bool checkCollision(Line* c) override;
        // void draw() override;
        // void gui() override;
    };
    
    class Circle : public AbstractCollider {
        public:
        float radius;
        Circle(float radius, glm::vec2 center = {});
        bool checkCollision(Rectangle* c) override;
        bool checkCollision(Circle* c) override;
        bool checkCollision(Line* c) override;
        // void draw() override;
        // void gui() override;
    };
    
    class Line : public AbstractCollider {
        public:
        float length;
        glm::vec2 direction;
        Line(float length, glm::vec2 direction, glm::vec2 origin = {});
        bool checkCollision(Rectangle* c) override;
        bool checkCollision(Circle* c) override;
        bool checkCollision(Line* c) override;
        // void draw() override;
        // void gui() override;
    };
}

