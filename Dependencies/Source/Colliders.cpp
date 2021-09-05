#include "Colliders.h"


namespace Umbra2D {
    bool Rectangle::checkCollision(Rectangle* c) {return false;}
    bool Rectangle::checkCollision(Circle* c) {return false;}
    bool Rectangle::checkCollision(Line* c) {return false;}

    bool Circle::checkCollision(Rectangle* c) {return false;}
    bool Circle::checkCollision(Circle* c) {return false;}
    bool Circle::checkCollision(Line* c) {return false;}

    bool Line::checkCollision(Rectangle* c) {return false;}
    bool Line::checkCollision(Circle* c) {return false;}
    bool Line::checkCollision(Line* c) {return false;}


    //! TODO 
    void Rectangle::draw() {}
    void Rectangle::gui() {}

    void Circle::draw() {}
    void Circle::gui() {}

    void Line::draw() {}
    void Line::gui() {}
}