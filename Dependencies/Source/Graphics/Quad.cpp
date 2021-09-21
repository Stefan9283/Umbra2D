#include "Umbra2D.h"

namespace Umbra2D::Graphics {
    Quad::Quad() {
        std::vector<Vertex> vertices{
                { glm::vec2(-0.5, -0.5), glm::vec2(0, 0) },
                { glm::vec2(-0.5,  0.5), glm::vec2(0, 1) },
                { glm::vec2( 0.5, -0.5), glm::vec2(1, 0) },
                { glm::vec2( 0.5,  0.5), glm::vec2(1, 1) },
        };
        std::vector<uint32_t> indices{0, 1, 2, 2, 1, 3};

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));

        glBindVertexArray(0);
    }
    Quad::~Quad() {
        glDeleteVertexArrays(1, &EBO);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
    void Quad::draw() {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, (GLsizei)6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
    void Quad::drawN(unsigned int N) {
        glBindVertexArray(VAO);
        glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)6, GL_UNSIGNED_INT, nullptr, N);
        glBindVertexArray(0);
    }


    DynamicQuad::DynamicQuad() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    void DynamicQuad::bindVAO() {
        glBindVertexArray(VAO);
    }
    void DynamicQuad::setVBO(Vertex* vertices) {
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * sizeof(Vertex), vertices);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    void DynamicQuad::draw() {
        // render quad
        bindVAO();
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    DynamicQuad::~DynamicQuad() {
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
}
