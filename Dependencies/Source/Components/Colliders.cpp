#include "Components/Colliders.h"
#include "Graphics/Shader.h"
#include "AssetLibrary.h"
#include "Graphics/Quad.h"
#include "Engines/Engine.h"
#include "Entity.h"
#include "Components/PropertyComponent.h"

extern Umbra2D::Umbra2DEngine* umbra;
#define colliderShader umbra->colliderShader

#define CIRCLE_SHAPE 0
#define AARECTANGLE_SHAPE 1
#define LINE_SHAPE 2
#define RECTANGLE_SHAPE 1

// geeksforgeeks adapted code
bool onSegment(glm::vec2 p, glm::vec2 q, glm::vec2 r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;

    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(glm::vec2 p, glm::vec2 q, glm::vec2 r)
{
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    float val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // collinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(glm::vec2 p1, glm::vec2 q1, glm::vec2 p2, glm::vec2 q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false; // Doesn't fall in any of the above cases
}
// end of adapted code

namespace Umbra2D::Components::Colliders {
    // TODO
    bool Rectangle::checkCollision(Components::Colliders::Rectangle *c) { return false; }
    // TODO
    bool Rectangle::checkCollision(Components::Colliders::AARectangle *c) { return false; }
    // TODO
    bool Rectangle::checkCollision(Components::Colliders::Circle *c) { return false; }
    // TODO
    bool Rectangle::checkCollision(Components::Colliders::Line *c) { return false; }

    bool AARectangle::checkCollision(AARectangle* c) {
        auto posThis = getPosition();
        auto posC    = c->getPosition();

        glm::vec2 rightSideUpSide1 = posThis + this->dimensions / 2.f;
        glm::vec2 rightSideUpSide2 = posC + c->dimensions / 2.f;
        glm::vec2 leftSideDownSide1 = posThis - this->dimensions / 2.f;
        glm::vec2 leftSideDownSide2 = posC - c->dimensions / 2.f;

        return (rightSideUpSide1.x >= leftSideDownSide2.x && leftSideDownSide1.x <= rightSideUpSide2.x) &&
               (rightSideUpSide1.y >= leftSideDownSide2.y && leftSideDownSide1.y <= rightSideUpSide2.y);
    }
    bool AARectangle::checkCollision(Circle* c) {
        auto posThis = getPosition();
        auto posC    = c->getPosition();

        glm::vec2 rightSideUpSide = posThis + this->dimensions / 2.f;
        glm::vec2 leftSideDownSide = posThis - this->dimensions / 2.f;

        // lower left corner
        float x1 = leftSideDownSide.x;
        float y1 = leftSideDownSide.y;

        // upper right corner
        float x2 = rightSideUpSide.x;
        float y2 = rightSideUpSide.y;

        // centre of circle
        float xc = posC.x;
        float yc = posC.y;

        // find nearest point to centre of circle
        // on both axis
        float xn = max(x1, min(xc, x2));
        float yn = max(y1, min(yc, y2));

        // distance between centre of circle and
        // the found nearest point
        float Dx = xn - xc;
        float Dy = yn - yc;

        return (Dx * Dx + Dy * Dy) <= c->radius * c->radius;
    }
    bool AARectangle::checkCollision(Line* c) {
        auto posThis = getPosition();
        auto posC    = c->getPosition();

        // first point of line
        glm::vec2 startPoint = posC;

        // end point of line
        glm::vec2 endPoint = posC + c->length * c->direction;

        // corner points of rectangle, starting from top left corner
        // and going clockwise
        glm::vec2 p1 = { posThis.x - this->dimensions.x / 2.f, posThis.y + this->dimensions.y / 2.f };
        glm::vec2 p2 = { posThis.x + this->dimensions.x / 2.f, posThis.y + this->dimensions.y / 2.f };
        glm::vec2 p3 = { posThis.x + this->dimensions.x / 2.f, posThis.y - this->dimensions.y / 2.f };
        glm::vec2 p4 = { posThis.x - this->dimensions.x / 2.f, posThis.y - this->dimensions.y / 2.f };

        // intersection with all sides of rectangle
        bool flag = doIntersect(startPoint, endPoint, p1, p2) || doIntersect(startPoint, endPoint, p2, p3) ||
                    doIntersect(startPoint, endPoint, p3, p4) || doIntersect(startPoint, endPoint, p4, p1);

        // check if line is inside rectangle
        if (!flag) {
            return startPoint.x >= p1.x && startPoint.x <= p3.x &&
                   startPoint.y >= p3.y && startPoint.y <= p1.y;
        }
        else {
            return flag;
        }
    }
    bool AARectangle::checkCollision(Components::Colliders::Rectangle *c) {
        return c->checkCollision(this);
    }

    bool Circle::checkCollision(AARectangle* c) {
        return c->checkCollision(this);
    }
    bool Circle::checkCollision(Circle* c) {
        auto posThis = getPosition();
        auto posC    = c->getPosition();
        return this->radius + c->radius >= glm::length(posThis - posC);
    }
    bool Circle::checkCollision(Line* c) {
        auto posThis = getPosition();
        auto posC    = c->getPosition();

        // first point of line
        glm::vec2 startPoint = posC;

        // end point of line
        glm::vec2 endPoint = posC + c->length * c->direction;

        // get projection on line from centre of circle
        glm::vec2 projectedPoint = glm::closestPointOnLine(posThis, startPoint, endPoint);

        // distance from centre of circle to projected point
        float Dx = posThis.x - projectedPoint.x;
        float Dy = posThis.y - projectedPoint.y;

        return (Dx * Dx + Dy * Dy) <= this->radius * this->radius;
    }
    bool Circle::checkCollision(Components::Colliders::Rectangle *c) {
        return c->checkCollision(this);
    }

    bool Line::checkCollision(AARectangle* c) {
        return c->checkCollision(this);
    }
    bool Line::checkCollision(Circle* c) {
        return c->checkCollision(this);
    }
    bool Line::checkCollision(Line* c) {
        auto posThis = getPosition();
        auto posC    = c->getPosition();

        // start and end point of first line
        glm::vec2 startPoint1 = posThis;
        glm::vec2 endPoint1 = posThis + this->direction * this->length;

        // start and end point of second line
        glm::vec2 startPoint2 = posC;
        glm::vec2 endPoint2 = posC + c->direction * c->length;

        return doIntersect(startPoint1, endPoint1, startPoint2, endPoint2);
    }
    bool Line::checkCollision(Components::Colliders::Rectangle *c) {
        return c->checkCollision(this);
    }

    Rectangle::Rectangle(float height, float length, glm::vec2 center) {
        this->dimensions = glm::vec2(length, height) / 2.f;
        this->offset = center;
    }
    AARectangle::AARectangle(float height, float length, glm::vec2 center) : AbstractCollider() {
        this->dimensions = {length, height};
        this->offset = center;
    }
    Circle::Circle(float radius, glm::vec2 center) : AbstractCollider() {
        this->radius = radius;
        this->offset = center;
    }
    Line::Line(float length, glm::vec2 direction, glm::vec2 origin) : AbstractCollider() {
        this->length = length;
        this->direction = direction;
        this->offset = origin;
    }

    // TODO
    void Rectangle::draw(Umbra2D::Graphics::Shader* shader) {
        shader->setInt("shape", RECTANGLE_SHAPE);
        shader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
//        auto translation = pos;
//        if (getParent()->hasComponent<TRANSFORM>())
//            translation += getParent()->getComponent<TRANSFORM>()->toMat4();
//        glm::mat4 model =
//                glm::translate(glm::mat4(1), glm::vec3(translation.x, translation.y, 0)) *
//                glm::scale(glm::mat4(1), glm::vec3(dimensions.x, dimensions.y, 1));
//        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void AARectangle::draw(Umbra2D::Graphics::Shader* shader) {
        shader->setInt("shape", AARECTANGLE_SHAPE);
        shader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(getPosition(), 0)) *
                glm::scale(glm::mat4(1), glm::vec3(dimensions.x, dimensions.y, 1));
        shader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void Circle::draw(Umbra2D::Graphics::Shader* shader) {
        shader->setInt("shape", CIRCLE_SHAPE);
        shader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(getPosition(), 0)) *
                glm::scale(glm::mat4(1), glm::vec3(glm::vec2(radius * 2.f), 1));
        shader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void Line::draw(Umbra2D::Graphics::Shader* shader) {
        shader->setInt("shape", LINE_SHAPE);
        shader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(getPosition(), 0)) *
                glm::rotate(glm::mat4(1),(float)(atan2(direction.y, direction.x) - 3.1415 / 2.),glm::vec3(0, 0, 1)) *
                glm::scale(glm::mat4(1), glm::vec3(thickness, length, 1)) *
                glm::translate(glm::mat4(1), glm::vec3(0, 0.5, 0));
        shader->setMat4("model", &model);
        LIBRARY->q->draw();
    }


    void AbstractCollider::gui() {
        std::string id = std::to_string(getParent()->getID());
        ImGui::InputFloat2(("offset col"), (float*)&offset);
    }

    glm::vec2 AbstractCollider::getPosition() {
        glm::vec2 translation = offset;
        if (getParent()->hasComponent<TRANSFORM>())
            translation += getParent()->getComponent<TRANSFORM>()->getPos();
        return translation;
    }

    void AARectangle::gui() {
        std::string id = std::to_string(getParent()->getID());
        if (ImGui::TreeNode(("AARectangle"))) {
            AbstractCollider::gui();
            ImGui::InputFloat2(("width/height rectangle"), (float *) &dimensions);
            ImGui::TreePop();
        }
    }
    void Circle::gui() {
        std::string id = std::to_string(getParent()->getID());
        if (ImGui::TreeNode(("Circle"))) {
            AbstractCollider::gui();
            ImGui::InputFloat(("radius circle"), &radius);
            ImGui::TreePop();
        }
    }
    void Line::gui() {
        std::string id = std::to_string(getParent()->getID());
        if (ImGui::TreeNode(("Line"))) {
            AbstractCollider::gui();
            if (ImGui::SliderFloat2(("direction line"), (float *) &direction, -1, 1))
                direction = glm::normalize(direction);
            ImGui::InputFloat(("Thickness"), &thickness, 1, 100);
            ImGui::InputFloat(("length line"), &length, 0.f, 1000.f);
            ImGui::TreePop();
        }
    }



    // TODO
    void Rectangle::gui() {
        std::string id = std::to_string(getParent()->getID());
        if (ImGui::TreeNode(("Rectangle"))) {
            AbstractCollider::gui();
        }
    }


}
