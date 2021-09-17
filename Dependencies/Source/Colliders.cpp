#include "Colliders.h"
#include "Shader.h"
#include "AssetLibrary.h"
#include "Quad.h"
#include "Engine.h"

long long unsigned int collidersCount = 0;
extern Umbra2D::Shader* colliderShader;
extern Umbra2D::Engine* umbra;

#define CIRCLE 0
#define RECTANGLE 1
#define LINE 2

namespace Umbra2D::Colliders {

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
        int val = (q.y - p.y) * (r.x - q.x) -
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

    bool Rectangle::checkCollision(Rectangle* c) {
        glm::vec2 rightSideUpSide1 = this->pos + this->dimensions / 2.f;
        glm::vec2 rightSideUpSide2 = c->pos + c->dimensions / 2.f;
        glm::vec2 leftSideDownSide1 = this->pos - this->dimensions / 2.f;
        glm::vec2 leftSideDownSide2 = c->pos - c->dimensions / 2.f;

        return (rightSideUpSide1.x >= leftSideDownSide2.x && leftSideDownSide1.x <= rightSideUpSide2.x) &&
            (rightSideUpSide1.y >= leftSideDownSide2.y && leftSideDownSide1.y <= rightSideUpSide2.y);
    }
    bool Rectangle::checkCollision(Circle* c) {
        glm::vec2 rightSideUpSide = this->pos + this->dimensions / 2.f;
        glm::vec2 leftSideDownSide = this->pos - this->dimensions / 2.f;

        // lower left corner
        int x1 = leftSideDownSide.x;
        int y1 = leftSideDownSide.y;

        // upper right corner
        int x2 = rightSideUpSide.x;
        int y2 = rightSideUpSide.y;

        // centre of circle
        int xc = c->pos.x;
        int yc = c->pos.y;

        // find nearest point to centre of circle
        // on both axis
        int xn = max(x1, min(xc, x2));
        int yn = max(y1, min(yc, y2));

        // distance between centre of circle and
        // the found nearest point
        int Dx = xn - xc;
        int Dy = yn - yc;

        return (Dx * Dx + Dy * Dy) <= c->radius * c->radius;

    }
    bool Rectangle::checkCollision(Line* c) {
        // first point of line
        glm::vec2 startPoint = c->pos;

        // end point of line
        glm::vec2 endPoint = c->pos + c->length * c->direction;

        // corner points of rectangle, starting from top left corner
        // and going clockwise
        glm::vec2 p1 = { this->pos.x - this->dimensions.x / 2.f, this->pos.y + this->dimensions.y / 2.f };
        glm::vec2 p2 = { this->pos.x + this->dimensions.x / 2.f, this->pos.y + this->dimensions.y / 2.f };
        glm::vec2 p3 = { this->pos.x + this->dimensions.x / 2.f, this->pos.y - this->dimensions.y / 2.f };
        glm::vec2 p4 = { this->pos.x - this->dimensions.x / 2.f, this->pos.y - this->dimensions.y / 2.f };

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

    bool Circle::checkCollision(Rectangle* c) {
        return c->checkCollision(this);
    }
    bool Circle::checkCollision(Circle* c) {
        return this->radius + c->radius >= glm::length(this->pos - c->pos);
    }
    bool Circle::checkCollision(Line* c) {
        // first point of line
        glm::vec2 startPoint = c->pos;

        // end point of line
        glm::vec2 endPoint = c->pos + c->length * c->direction;

        // get projection on line from centre of circle
        glm::vec2 projectedPoint = glm::closestPointOnLine(this->pos, startPoint, endPoint);

        // distance from centre of circle to projected point
        int Dx = this->pos.x - projectedPoint.x;
        int Dy = this->pos.y - projectedPoint.y;

        return (Dx * Dx + Dy * Dy) <= this->radius * this->radius;
    }

    bool Line::checkCollision(Rectangle* c) {
        return c->checkCollision(this);
    }
    bool Line::checkCollision(Circle* c) {
        return c->checkCollision(this);
    }
    bool Line::checkCollision(Line* c) {
        // start and end point of first line
        glm::vec2 startPoint1 = this->pos;
        glm::vec2 endPoint1 = this->pos + this->direction * this->length;

        // start and end point of second line
        glm::vec2 startPoint2 = c->pos;
        glm::vec2 endPoint2 = c->pos + c->direction * c->length;

        return doIntersect(startPoint1, endPoint1, startPoint2, endPoint2);
    }

    AbstractCollider::AbstractCollider() {
        id = collidersCount;
        collidersCount++;
    }

    Rectangle::Rectangle(float height, float length, glm::vec2 center) : AbstractCollider() {
        this->dimensions = {length, height};
        this->pos = center;
    }
    Circle::Circle(float radius, glm::vec2 center) : AbstractCollider() {
        this->radius = radius;
        this->pos = center;
    }
    Line::Line(float length, glm::vec2 direction, glm::vec2 origin) : AbstractCollider() {
        this->length = length;
        this->direction = direction;
        this->pos = origin;
    }


    /*void Rectangle::draw() {
        colliderShader->setInt("shape", RECTANGLE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 0)) *
                glm::scale(glm::mat4(1), glm::vec3(dimensions.x, dimensions.y, 1));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void Circle::draw() {
        colliderShader->setInt("shape", CIRCLE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 0)) *
                glm::scale(glm::mat4(1), glm::vec3(radius, radius, 1));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void Line::draw() {
        colliderShader->setInt("shape", LINE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        float halfLen = glm::length(this->pos + this->length * this->direction) / 2.f;

        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 0)) *
                glm::rotate(glm::mat4(1),
                        (float)(atan2(direction.y, direction.x) - 3.1415 / 2.),
                        glm::vec3(0, 0, 1)) *
                glm::scale(glm::mat4(1), glm::vec3(thickness, halfLen, 1));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }

    void AbstractCollider::gui() {
        ImGui::SliderFloat2(("position col " + std::to_string(id)).c_str(), (float*)&pos, -100000, 100000);
    }
    void Rectangle::gui() {
        AbstractCollider::gui();
        ImGui::SliderFloat2(("height/width rectangle " + std::to_string(id)).c_str(), (float*)&dimensions, 0, 10000);
    }
    void Circle::gui() {
        AbstractCollider::gui();
        ImGui::SliderFloat(("radius circle " + std::to_string(id)).c_str(), &radius, 0, 1000);
    }
    void Line::gui() {
        AbstractCollider::gui();
        if (ImGui::SliderFloat2(("direction line " + std::to_string(id)).c_str(), (float*)&direction, -1, 1))
            direction = glm::normalize(direction);
        ImGui::SliderFloat(("Thickness "+ std::to_string(id)).c_str(), &thickness, 1, 100);
        ImGui::SliderFloat(("length line " + std::to_string(id)).c_str(), &length, 0.f, 1000.f);
    }*/
    void Rectangle::draw() {
        colliderShader->setInt("shape", RECTANGLE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
            glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 0)) *
            glm::scale(glm::mat4(1), glm::vec3(dimensions.x, dimensions.y, 1));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void Circle::draw() {
        colliderShader->setInt("shape", CIRCLE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
            glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 0)) *
            glm::scale(glm::mat4(1), glm::vec3(glm::vec2(radius * 2.f), 1));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void Line::draw() {
        colliderShader->setInt("shape", LINE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
            glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 0)) *
            glm::rotate(glm::mat4(1), (float)(atan2(direction.y, direction.x) - 3.1415 / 2.), glm::vec3(0, 0, 1)) *
            glm::scale(glm::mat4(1), glm::vec3(thickness, length, 1)) *
            glm::translate(glm::mat4(1), glm::vec3(0, 0.5, 0));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }

    void AbstractCollider::gui() {
        ImGui::SliderFloat2(("position col " + std::to_string(id)).c_str(), (float*)&pos, -1000, 1000);
    }
    void Rectangle::gui() {
        AbstractCollider::gui();
        ImGui::SliderFloat2(("height/width rectangle " + std::to_string(id)).c_str(), (float*)&dimensions, 0, 100);
    }
    void Circle::gui() {
        AbstractCollider::gui();
        ImGui::SliderFloat(("radius circle " + std::to_string(id)).c_str(), &radius, 0, 1000);
    }
    void Line::gui() {
        AbstractCollider::gui();
        if (ImGui::SliderFloat2(("direction line " + std::to_string(id)).c_str(), (float*)&direction, -1, 1))
            direction = glm::normalize(direction);
        ImGui::SliderFloat(("Thickness " + std::to_string(id)).c_str(), &thickness, 1, 100);
        ImGui::SliderFloat(("length line " + std::to_string(id)).c_str(), &length, 0.f, 1000.f);
    }
}
