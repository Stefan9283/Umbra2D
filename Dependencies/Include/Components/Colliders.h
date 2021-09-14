#pragma once

#include "Common.h"
#include "Component.h"

namespace Umbra2D::Components::Colliders {
    class AbstractCollider : public Umbra2D::Components::Component {
        public:
        long long unsigned int id;
        glm::vec2 pos;

        AbstractCollider();
        virtual ~AbstractCollider() = default;

        virtual bool checkCollision(Components::Colliders::Rectangle* c) = 0;
        virtual bool checkCollision(Components::Colliders::Circle* c) = 0;
        virtual bool checkCollision(Components::Colliders::Line* c) = 0;

        virtual void draw() = 0;
        virtual void gui() = 0;
    };
    
    class Rectangle : public AbstractCollider {
        public:
        glm::vec2 dimensions;

        Rectangle(float height, float length, glm::vec2 center = {});

        bool checkCollision(Components::Colliders::Rectangle* c) override;
        bool checkCollision(Components::Colliders::Circle* c) override;
        bool checkCollision(Components::Colliders::Line* c) override;

        void draw() override;
        void gui() override;
    };
    
    class Circle : public AbstractCollider {
        public:
        float radius;

        Circle(float radius, glm::vec2 center = {});

        bool checkCollision(Components::Colliders::Rectangle* c) override;
        bool checkCollision(Components::Colliders::Circle* c) override;
        bool checkCollision(Components::Colliders::Line* c) override;

        void draw() override;
        void gui() override;
    };
    
    class Line : public AbstractCollider {
        public:
        float length;
        float thickness = 5;
        glm::vec2 direction;

        Line(float length, glm::vec2 direction, glm::vec2 origin = {});

        bool checkCollision(Components::Colliders::Rectangle* c) override;
        bool checkCollision(Components::Colliders::Circle* c) override;
        bool checkCollision(Components::Colliders::Line* c) override;

        void draw() override;
        void gui() override;
    };
}

