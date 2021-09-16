#pragma once

#include "Common.h"
#include "Component.h"

namespace Umbra2D::Components::Colliders {
    class AbstractCollider : public COMPONENT {
        public:
        glm::vec2 pos; // TODO rename to offset

        AbstractCollider() = default;
        virtual ~AbstractCollider() = default;

        virtual bool checkCollision(Components::Colliders::Rectangle* c) = 0;
        virtual bool checkCollision(Components::Colliders::Circle* c) = 0;
        virtual bool checkCollision(Components::Colliders::Line* c) = 0;

        virtual void draw() = 0;
        void gui() override;
    };
    // axis aligned rectangle
    class Rectangle : public AbstractCollider {
        public:
        glm::vec2 dimensions;

        Rectangle(float height = 1, float length = 1, glm::vec2 center = {});

        bool checkCollision(Components::Colliders::Rectangle* c) override;
        bool checkCollision(Components::Colliders::Circle* c) override;
        bool checkCollision(Components::Colliders::Line* c) override;

        void draw() override;
        void gui() override;
    };
    
    class Circle : public AbstractCollider {
        public:
        float radius;

        Circle(float radius = 1, glm::vec2 center = {});

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

        Line(float length = 1, glm::vec2 direction = glm::vec2(0, 1), glm::vec2 origin = {});

        bool checkCollision(Components::Colliders::Rectangle* c) override;
        bool checkCollision(Components::Colliders::Circle* c) override;
        bool checkCollision(Components::Colliders::Line* c) override;

        void draw() override;
        void gui() override;
    };
}

