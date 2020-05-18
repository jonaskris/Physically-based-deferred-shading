#pragma once

#include <vector>
#include <cstdint>
#include <iostream>

#include <glad/glad.h>

#include <VertexAttribute.h>

namespace math::geometry
{
    class Geometry
    {
    private:
        std::vector<float> vertices;
        std::vector<VertexAttribute> vertexAttributes;

        std::vector<uint32_t> indices;

        GLenum drawMode;

    public:
        Geometry(const std::vector<float>& vertices, const std::vector<VertexAttribute>& vertexAttributes, const std::vector<uint32_t>& indices, GLenum drawMode)
        : vertices(vertices), vertexAttributes(vertexAttributes), indices(indices), drawMode(drawMode) {}
    
        const std::vector<float>& getVertices() const { return vertices; }
        const std::vector<uint32_t>& getIndices() const { return indices; }
        const std::vector<VertexAttribute>& getVertexAttributes() const { return vertexAttributes; }
        GLenum getDrawMode() const { return drawMode; }

        friend std::ostream& operator<<(std::ostream& out, const Geometry& geometry)
        {
            out << "Geometry: Vertices size: " << geometry.vertices.size() << ", vertexAttributes size: " << geometry.vertexAttributes.size() << ", indices size: " << geometry.indices.size() << ", drawmode: " << geometry.drawMode <<  std::endl;
        }
    };
}