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
        std::vector<float> vertices;
        std::vector<uint32_t> indices;
        GLuint VAO;
        GLuint VBO;
        GLuint IBO;

        void initialize(const std::vector<VertexAttribute>& vertexAttributes);

    public:
        Mesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<VertexAttribute>& vertexAttributes, unsigned int drawmode);

        void draw() const;

        friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
        {
            out << "Mesh: Vertices size: " << mesh.vertices.size() << ", Indices size: " << mesh.indices.size();
            return out;
        }
    };
}