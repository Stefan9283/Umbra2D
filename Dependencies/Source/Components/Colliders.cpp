#include "Components/Colliders.h"
#include "Graphics/Shader.h"
#include "AssetLibrary.h"
#include "Graphics/Quad.h"
#include "Engines/Engine.h"
#include "Entity.h"

long long unsigned int collidersCount = 0;
extern Umbra2D::Umbra2DEngine* umbra;
#define colliderShader umbra->colliderShader

#define CIRCLE_SHAPE 0
#define RECTANGLE_SHAPE 1
#define LINE_SHAPE 2


namespace Umbra2D::Components::Colliders {
    bool Rectangle::checkCollision(Rectangle* c) {
        glm::vec2 rightSideUpSide1 = this->pos + this->dimensions / 2.f;
        glm::vec2 rightSideUpSide2 = c->pos + c->dimensions / 2.f;
        glm::vec2 leftSideDownSide1 = this->pos - this->dimensions / 2.f;
        glm::vec2 leftSideDownSide2 = c->pos - c->dimensions / 2.f;

        return (rightSideUpSide1.x >= leftSideDownSide2.x && leftSideDownSide1.x <= rightSideUpSide2.x) &&
               (rightSideUpSide1.y >= leftSideDownSide2.y && leftSideDownSide1.y <= rightSideUpSide2.y);
    }
    bool Rectangle::checkCollision(Circle* c) {
        glm::vec2 rightSideUpSide1 = this->pos + this->dimensions / 2.f;
        glm::vec2 rightSideUpSide2 = c->pos + c->radius / 2.f;
        glm::vec2 leftSideDownSide1 = this->pos - this->dimensions / 2.f;
        glm::vec2 leftSideDownSide2 = c->pos - c->radius / 2.f;

        return (rightSideUpSide1.x >= leftSideDownSide2.x && leftSideDownSide1.x <= rightSideUpSide2.x) &&
               (rightSideUpSide1.y >= leftSideDownSide2.y && leftSideDownSide1.y <= rightSideUpSide2.y);
    }
    bool Rectangle::checkCollision(Line* c) {return false;}

    bool Circle::checkCollision(Rectangle* c) {
        glm::vec2 rightSideUpSide1 = this->pos + this->radius / 2.f;
        glm::vec2 rightSideUpSide2 = c->pos + c->dimensions / 2.f;
        glm::vec2 leftSideDownSide1 = this->pos - this->radius / 2.f;
        glm::vec2 leftSideDownSide2 = c->pos - c->dimensions / 2.f;

        return (rightSideUpSide1.x >= leftSideDownSide2.x && leftSideDownSide1.x <= rightSideUpSide2.x) &&
               (rightSideUpSide1.y >= leftSideDownSide2.y && leftSideDownSide1.y <= rightSideUpSide2.y);
    }
    bool Circle::checkCollision(Circle* c) {
        return this->radius + c->radius >= glm::length(this->pos - c->pos);
    }
    bool Circle::checkCollision(Line* c) {return false;}

    bool Line::checkCollision(Rectangle* c) {return false;}
    bool Line::checkCollision(Circle* c) {return false;}
    bool Line::checkCollision(Line* c) {return false;}

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

    void Rectangle::draw() {
        colliderShader->setInt("shape", RECTANGLE_SHAPE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 0)) *
                glm::scale(glm::mat4(1), glm::vec3(dimensions.x, dimensions.y, 1));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void Circle::draw() {
        colliderShader->setInt("shape", CIRCLE_SHAPE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 0)) *
                glm::scale(glm::mat4(1), glm::vec3(radius, radius, 1));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void Line::draw() {
        colliderShader->setInt("shape", LINE_SHAPE);
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
        ImGui::Text("Rectangle %d", this->getParent()->getID());
        AbstractCollider::gui();
        ImGui::SliderFloat2(("height/width rectangle " + std::to_string(id)).c_str(), (float*)&dimensions, 0, 10000);
    }
    void Circle::gui() {
        ImGui::Text("Circle %d", this->getParent()->getID());
        AbstractCollider::gui();
        ImGui::SliderFloat(("radius circle " + std::to_string(id)).c_str(), &radius, 0, 1000);
    }
    void Line::gui() {
        ImGui::Text("Line %d", this->getParent()->getID());
        AbstractCollider::gui();
        if (ImGui::SliderFloat2(("direction line " + std::to_string(id)).c_str(), (float*)&direction, -1, 1))
            direction = glm::normalize(direction);
        ImGui::SliderFloat(("Thickness "+ std::to_string(id)).c_str(), &thickness, 1, 100);
        ImGui::SliderFloat(("length line " + std::to_string(id)).c_str(), &length, 0.f, 1000.f);
    }
}
