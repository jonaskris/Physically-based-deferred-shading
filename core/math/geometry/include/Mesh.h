#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vec3.h>
#include <Vertex.h>

class MeshBase
{
protected:
    virtual void initialize() = 0;

public:
    virtual void draw() const = 0;
};

template <typename VertexType, unsigned int DrawMode>
class Mesh : public MeshBase
{
protected:
    std::vector<VertexType> vertices;
    std::vector<uint32_t> indices;
    GLuint VAO;
    GLuint VBO;
    GLuint IBO;

    void initialize() override
    {
        // VBO
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
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

        VertexType::describeVAOLayout();

        glBindVertexArray(0);
    }

public:
    Mesh(const std::vector<VertexType>& verticesIn, const std::vector<uint32_t>& indicesIn) 
    {
        vertices = verticesIn;
        indices = indicesIn;
        
        initialize();
    };

    void draw() const override
    {
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        glDrawElements(DrawMode, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
    {
        out << "Mesh: Vertices size: " << mesh.vertices.size() << ", Indices size: " << mesh.indices.size();
        return out;
    }
};