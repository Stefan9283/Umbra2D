#include "Quad.h"

struct Vertex {
    glm::vec2 position;
    glm::vec2 texture;
};

namespace Umbra2D {
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
    void Quad::Draw() {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, (GLsizei)6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}