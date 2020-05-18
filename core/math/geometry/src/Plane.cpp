#include <Plane.h>

#include <vector>
#include <cstdint>

#include <Geometry.h>
#include <VertexAttribute.h>

namespace math::geometry
{
    namespace Plane
    {
        Geometry generate()
        {
            Workspace workspace;
            workspace.generate();

            std::vector<VertexAttribute> vertexAttributes
            {
                // Position
                VertexAttribute{defines::VertexAttribute::POSITION, 0, defines::NumeralType::VEC3, GL_FLOAT, false, 8 * sizeof(float), 0},

                // Normal
                VertexAttribute{defines::VertexAttribute::NORMAL, 1, defines::NumeralType::VEC3, GL_FLOAT, true, 8 * sizeof(float), (const void*)(3 * sizeof(float))},

                // Uv
                VertexAttribute{defines::VertexAttribute::UV, 2, defines::NumeralType::VEC2, GL_FLOAT, true, 8 * sizeof(float), (const void*)(6 * sizeof(float))}
            };

            return Geometry(workspace.vertices, vertexAttributes, workspace.indices, GL_TRIANGLES);
        }
    }
}