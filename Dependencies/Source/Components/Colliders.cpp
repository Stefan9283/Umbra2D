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

namespace Umbra2D::Components::Colliders {
    // TODO
    bool Rectangle::checkCollision(Components::Colliders::Rectangle *c) { return false; }
    // TODO
    bool Rectangle::checkCollision(Components::Colliders::Circle *c) { return false; }
    // TODO
    bool Rectangle::checkCollision(Components::Colliders::Line *c) { return false; }
    bool AARectangle::checkCollision(Rectangle* c) {
        glm::vec2 rightSideUpSide1 = this->pos + this->dimensions / 2.f;
        glm::vec2 rightSideUpSide2 = c->pos + c->dimensions / 2.f;
        glm::vec2 leftSideDownSide1 = this->pos - this->dimensions / 2.f;
        glm::vec2 leftSideDownSide2 = c->pos - c->dimensions / 2.f;

        return (rightSideUpSide1.x >= leftSideDownSide2.x && leftSideDownSide1.x <= rightSideUpSide2.x) &&
               (rightSideUpSide1.y >= leftSideDownSide2.y && leftSideDownSide1.y <= rightSideUpSide2.y);
    }
    bool AARectangle::checkCollision(Circle* c) {
        glm::vec2 rightSideUpSide1 = this->pos + this->dimensions / 2.f;
        glm::vec2 rightSideUpSide2 = c->pos + c->radius / 2.f;
        glm::vec2 leftSideDownSide1 = this->pos - this->dimensions / 2.f;
        glm::vec2 leftSideDownSide2 = c->pos - c->radius / 2.f;

        return (rightSideUpSide1.x >= leftSideDownSide2.x && leftSideDownSide1.x <= rightSideUpSide2.x) &&
               (rightSideUpSide1.y >= leftSideDownSide2.y && leftSideDownSide1.y <= rightSideUpSide2.y);
    }
    bool AARectangle::checkCollision(Line* c) {return false;}

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

    Rectangle::Rectangle(float height, float length, glm::vec2 center) {
        dimensions = glm::vec2(length, height) / 2.f;
        pos = center;
    }
    AARectangle::AARectangle(float height, float length, glm::vec2 center) : AbstractCollider() {
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

    // TODO
    void Rectangle::draw() {
        colliderShader->setInt("shape", RECTANGLE_SHAPE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
//        auto translation = pos;
//        if (getParent()->hasComponent<TRANSFORM>())
//            translation += getParent()->getComponent<TRANSFORM>()->toMat4();
//        glm::mat4 model =
//                glm::translate(glm::mat4(1), glm::vec3(translation.x, translation.y, 0)) *
//                glm::scale(glm::mat4(1), glm::vec3(dimensions.x, dimensions.y, 1));
//        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void AARectangle::draw() {
        colliderShader->setInt("shape", AARECTANGLE_SHAPE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        auto translation = pos;
        if (getParent()->hasComponent<TRANSFORM>())
            translation += getParent()->getComponent<TRANSFORM>()->getPos();
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(translation.x, translation.y, 0)) *
                glm::scale(glm::mat4(1), glm::vec3(dimensions.x, dimensions.y, 1));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void Circle::draw() {
        colliderShader->setInt("shape", CIRCLE_SHAPE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));

        auto translation = pos;
        if (getParent()->hasComponent<TRANSFORM>())
            translation += getParent()->getComponent<TRANSFORM>()->getPos();
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(translation.x, translation.y, 0)) *
                glm::scale(glm::mat4(1), glm::vec3(radius, radius, 1));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }
    void Line::draw() {
        colliderShader->setInt("shape", LINE_SHAPE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        float halfLen = glm::length(this->pos + this->length * this->direction) / 2.f;
        auto translation = pos;
        if (getParent()->hasComponent<TRANSFORM>())
            translation += getParent()->getComponent<TRANSFORM>()->getPos();
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(translation.x, translation.y, 0)) *
                glm::rotate(glm::mat4(1),
                        (float)(atan2(direction.y, direction.x) - 3.1415 / 2.),
                        glm::vec3(0, 0, 1)) *
                glm::scale(glm::mat4(1), glm::vec3(thickness, halfLen, 1));
        colliderShader->setMat4("model", &model);
        LIBRARY->q->draw();
    }

    void AbstractCollider::gui() {
        std::string id = std::to_string(getParent()->getID());
        ImGui::SliderFloat2(("position col " + id).c_str(), (float*)&pos, -100000, 100000);
    }
    void AARectangle::gui() {
        std::string id = std::to_string(getParent()->getID());
        if (ImGui::TreeNode(("AARectangle " + id).c_str())) {
            AbstractCollider::gui();
            ImGui::SliderFloat2(("height/width rectangle " + id).c_str(), (float *) &dimensions, 0, 10000);
            ImGui::TreePop();
        }
    }
    void Circle::gui() {
        std::string id = std::to_string(getParent()->getID());
        if (ImGui::TreeNode(("Circle " + id).c_str())) {
            AbstractCollider::gui();
            ImGui::SliderFloat(("radius circle " + id).c_str(), &radius, 0, 1000);
            ImGui::TreePop();
        }
    }
    void Line::gui() {
        std::string id = std::to_string(getParent()->getID());
        if (ImGui::TreeNode(("Line " + id).c_str())) {
            AbstractCollider::gui();
            if (ImGui::SliderFloat2(("direction line " + id).c_str(), (float *) &direction, -1, 1))
                direction = glm::normalize(direction);
            ImGui::SliderFloat(("Thickness " + id).c_str(), &thickness, 1, 100);
            ImGui::SliderFloat(("length line " + id).c_str(), &length, 0.f, 1000.f);
            ImGui::TreePop();
        }
    }
    // TODO
    void Rectangle::gui() {
        std::string id = std::to_string(getParent()->getID());
        if (ImGui::TreeNode(("Rectangle " + id).c_str())) {
            AbstractCollider::gui();
        }
    }
}
