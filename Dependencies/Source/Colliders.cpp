#include "Colliders.h"
#include "Shader.h"
#include "AssetLibrary.h"
#include "Quad.h"

long long unsigned int collidersCount = 0;
extern Umbra2D::Shader* colliderShader;
extern Umbra2D::AssetLibrary* lib;

#define CIRCLE 0
#define RECTANGLE 1
#define LINE 2

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
        colliderShader->setInt("shape", RECTANGLE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 0)) *
                glm::scale(glm::mat4(1), glm::vec3(dimensions.x, dimensions.y, 1));
        colliderShader->setMat4("model", &model);
        lib->q->draw();
    }
    void Circle::draw() {
        colliderShader->setInt("shape", CIRCLE);
        colliderShader->setVec4("color", glm::vec4(0.2, 0.2, 0.5, 0.4));
        glm::mat4 model =
                glm::translate(glm::mat4(1), glm::vec3(pos.x, pos.y, 0)) *
                glm::scale(glm::mat4(1), glm::vec3(radius, radius, 1));
        colliderShader->setMat4("model", &model);
        lib->q->draw();
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
        lib->q->draw();
    }

    void AbstractCollider::gui() {
        float p[]{pos.x, pos.y};
        if (ImGui::SliderFloat2(("position col " + std::to_string(id)).c_str(), p, -100000, 100000)) {
            pos = glm::vec2(p[0], p[1]);
        }
    }
    void Rectangle::gui() {
        AbstractCollider::gui();
        float dim[]{dimensions.x, dimensions.y};
        if (ImGui::SliderFloat2(("height/width rectangle " + std::to_string(id)).c_str(), dim, 0, 10000)) {
            dimensions = glm::vec2(dim[0], dim[1]);
        }
    }
    void Circle::gui() {
        AbstractCollider::gui();
        ImGui::SliderFloat(("radius circle " + std::to_string(id)).c_str(), &radius, 0, 1000);
    }
    void Line::gui() {
        AbstractCollider::gui();
        float dir[]{direction.x, direction.y};
        if (ImGui::SliderFloat2(("direction line " + std::to_string(id)).c_str(), dir, -1, 1)) {
            direction = glm::normalize(glm::vec2(dir[0], dir[1]));
        }
        ImGui::SliderFloat(("Thickness "+ std::to_string(id)).c_str(), &thickness, 1, 100);

        ImGui::SliderFloat(("length line " + std::to_string(id)).c_str(), &length, 0.f, 1000.f);
    }
}
