#pragma once

#include "Common.h"
#include "Component.h"

namespace Umbra2D::Components::Colliders {
    class AbstractCollider : public COMPONENT {
        public:
        glm::vec2 offset;

        AbstractCollider() = default;
        virtual ~AbstractCollider() = default;

        glm::vec2 getPosition();

        virtual bool checkCollision(Components::Colliders::Rectangle* c) = 0;
        virtual bool checkCollision(Components::Colliders::AARectangle* c) = 0;
        virtual bool checkCollision(Components::Colliders::Circle* c) = 0;
        virtual bool checkCollision(Components::Colliders::Line* c) = 0;

        virtual void draw(Shader* s) = 0;
        void gui() override;
    };
    // TODO
    class Rectangle : public AbstractCollider {
    public:
        glm::vec2 dimensions;

        Rectangle(float height = 1, float length = 1, glm::vec2 center = {});

        bool checkCollision(Components::Colliders::Rectangle* c) override;
        bool checkCollision(Components::Colliders::AARectangle* c) override;
        bool checkCollision(Components::Colliders::Circle* c) override;
        bool checkCollision(Components::Colliders::Line* c) override;

        void draw(Shader* s) override;
        void gui() override;
    };
    // axis aligned rectangle
    class AARectangle : public AbstractCollider {
    public:
        glm::vec2 dimensions;

        AARectangle(float height = 1, float length = 1, glm::vec2 center = {});

        bool checkCollision(Components::Colliders::Rectangle* c) override;
        bool checkCollision(Components::Colliders::AARectangle* c) override;
        bool checkCollision(Components::Colliders::Circle* c) override;
        bool checkCollision(Components::Colliders::Line* c) override;

        void draw(Shader* s) override;
        void gui() override;
    };
    class Circle : public AbstractCollider {
        public:
        float radius;

        Circle(float radius = 1, glm::vec2 center = {});

        bool checkCollision(Components::Colliders::Rectangle* c) override;
        bool checkCollision(Components::Colliders::AARectangle* c) override;
        bool checkCollision(Components::Colliders::Circle* c) override;
        bool checkCollision(Components::Colliders::Line* c) override;

        void draw(Shader* s) override;
        void gui() override;
    };
    
    class Line : public AbstractCollider {
        public:
        float length;
        float thickness = 5;
        glm::vec2 direction;

        Line(float length = 1, glm::vec2 direction = glm::vec2(0, 1), glm::vec2 origin = {});

        bool checkCollision(Components::Colliders::Rectangle* c) override;
        bool checkCollision(Components::Colliders::AARectangle* c) override;
        bool checkCollision(Components::Colliders::Circle* c) override;
        bool checkCollision(Components::Colliders::Line* c) override;

        void draw(Shader* s) override;
        void gui() override;
    };
}

