#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

#include <Vec3.h>
#include <VertexAttribute.h>

namespace graphics
{
    class Mesh
    {
    protected:
        unsigned int drawmode;
        unsigned int verticesSize;
        unsigned int indicesSize;
        GLuint VAO;
        GLuint VBO;
        GLuint IBO;

        void initialize(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<VertexAttribute>& vertexAttributes);

    public:
        Mesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<VertexAttribute>& vertexAttributes, unsigned int drawmode);

        void draw() const;

        friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
        {
            out << "Mesh: Vertices size: " << mesh.verticesSize << ", Indices size: " << mesh.indicesSize;
            return out;
        }
    };
}