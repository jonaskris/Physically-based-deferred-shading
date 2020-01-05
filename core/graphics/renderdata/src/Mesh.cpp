#include <Mesh.h>

#include <iostream>
#include <vector>

#include <glad/glad.h>

#include <Vec3.h>
#include <VertexAttribute.h>

namespace graphics
{
    void Mesh::initialize(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<VertexAttribute>& vertexAttributes)
    {
        // VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // IBO
        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indices.size(), &indices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // VAO
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        for(auto va : vertexAttributes)
        {
            glEnableVertexAttribArray(va.index);
            glVertexAttribPointer(va.index, va.size, va.type, va.normalized, va.stride, va.offset);
        }

        glBindVertexArray(0);
    }

    Mesh::Mesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<VertexAttribute>& vertexAttributes, unsigned int drawmode) 
    : drawmode(drawmode), verticesSize(vertices.size()), indicesSize(indices.size()) { initialize(vertices, indices, vertexAttributes); }

    void Mesh::draw() const
    {
        glBindVertexArray(VAO);
        glDrawElements(drawmode, indicesSize, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}