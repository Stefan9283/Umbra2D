#include "Colliders.h"

namespace Umbra2D::Colliders {
    bool Rectangle::checkCollision(Rectangle* c) {return false;}
    bool Rectangle::checkCollision(Circle* c) {return false;}
    bool Rectangle::checkCollision(Line* c) {return false;}

    bool Circle::checkCollision(Rectangle* c) {return false;}
    bool Circle::checkCollision(Circle* c) {return false;}
    bool Circle::checkCollision(Line* c) {return false;}

    bool Line::checkCollision(Rectangle* c) {return false;}
    bool Line::checkCollision(Circle* c) {return false;}
    bool Line::checkCollision(Line* c) {return false;}

    Rectangle::Rectangle(float height, float length, glm::vec2 center) {
        this->dimensions = {length, height};
        this->pos = center;
    }
    Circle::Circle(float radius, glm::vec2 center) {
        this->radius = radius;
        this->pos = center;
    }
    Line::Line(float length, glm::vec2 direction, glm::vec2 origin) {
        this->length = length;
        this->direction = direction;
        this->pos = origin;
    }

    //! TODO 
    // void Rectangle::draw() {}
    // void Rectangle::gui() {}

    // void Circle::draw() {}
    // void Circle::gui() {}

    // void Line::draw() {}
    // void Line::gui() {}
}