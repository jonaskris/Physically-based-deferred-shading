#pragma once

#include <vector>
#include <cstdint>

namespace Plane
{
    namespace
    {
        struct Workspace
        {
            std::vector<float> vertices;
            std::vector<uint32_t> indices;

            void generate()
            {
                vertices =
                {// |    Position     |     Normal     |    UV     |
                    -0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,    // Bottom left
                     0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,    // Bottom right
                     0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // Top right
                    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f     // Top left
                };

                indices =
                {
                    0, 1, 2,
                    2, 3, 0
                };
            }
        };
    }

    unsigned int generate();
};