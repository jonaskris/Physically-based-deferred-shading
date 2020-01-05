#include <Cube.h>

#include <vector>
#include <cstdint>

#include <Mesh.h>
#include <RenderData.h>
#include <VertexAttribute.h>

namespace Cube
{
    unsigned int generate(bool cubemapped)
    {
        Workspace workspace;
        workspace.generate(cubemapped);

        std::vector<graphics::VertexAttribute> vertexAttributes;

        if(cubemapped)
        {
            vertexAttributes =
            {
                // Position
                graphics::VertexAttribute{0, 3, GL_FLOAT, false, 6 * sizeof(float), (const void*)(0)},

                // Normal
                graphics::VertexAttribute{1, 3, GL_FLOAT, true, 6 * sizeof(float), (const void*)(3 * sizeof(float))}
            };
        } else
        {
            vertexAttributes =
            {
                // Position
                graphics::VertexAttribute{0, 3, GL_FLOAT, false, 8 * sizeof(float), (const void*)(0)},

                // Normal
                graphics::VertexAttribute{1, 3, GL_FLOAT, true, 8 * sizeof(float), (const void*)(3 * sizeof(float))},

                // Uv
                graphics::VertexAttribute{2, 2, GL_FLOAT, true, 8 * sizeof(float), (const void*)(6 * sizeof(float))}
            };
        }
        

        return graphics::RenderData::insert<graphics::Mesh>(
            new graphics::Mesh
            {
                workspace.vertices, workspace.indices, 
                vertexAttributes,
                (unsigned int)GL_TRIANGLES
            }
        );
    }
};