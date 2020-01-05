#pragma once

#include <vector>
#include <cstdint>

namespace Cube
{
    namespace
    {
        struct Workspace
        {
            std::vector<float> vertices;
            std::vector<uint32_t> indices;

            void generate(bool cubemapped)
            {
                if(cubemapped)
                {
                    vertices =
                    {
                    // Left
                    //  |    Position     |     Normal     |
                        -0.5f,-0.5f,-0.5f,-1.0f, 0.0f, 0.0f,
                        -0.5f,-0.5f, 0.5f,-1.0f, 0.0f, 0.0f,
                        -0.5f, 0.5f, 0.5f,-1.0f, 0.0f, 0.0f,
                        -0.5f, 0.5f,-0.5f,-1.0f, 0.0f, 0.0f,
                    // Right
                    //  |    Position     |     Normal     |
                         0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
                         0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f,
                         0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
                         0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
                    // Bottom
                    //  |    Position     |     Normal     |
                         0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f,
                         0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f,
                        -0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f,
                        -0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f,
                    // Top
                    //  |    Position     |     Normal     |
                         0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
                        -0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
                        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
                         0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
                    // Back
                    //  |    Position     |     Normal     |
                         0.5f, -0.5f,-0.5f, 0.0f, 0.0f,-1.0f,
                        -0.5f, -0.5f,-0.5f, 0.0f, 0.0f,-1.0f,
                        -0.5f,  0.5f,-0.5f, 0.0f, 0.0f,-1.0f,
                         0.5f,  0.5f,-0.5f, 0.0f, 0.0f,-1.0f,
                    // Front
                    //  |    Position     |     Normal     |
                         0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                         0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                        -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
                    };
                } else
                {
                    vertices =
                    {
                    // Left
                    //  |    Position     |     Normal     |    UV     |
                        -0.5f,-0.5f,-0.5f,-1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                        -0.5f,-0.5f, 0.5f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                        -0.5f, 0.5f, 0.5f,-1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                        -0.5f, 0.5f,-0.5f,-1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                    // Right
                    //  |    Position     |     Normal     |    UV     |
                         0.5f,-0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                         0.5f, 0.5f,-0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                         0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                         0.5f,-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                    // Bottom
                    //  |    Position     |     Normal     |    UV     |
                         0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f, 1.0f, 0.0f,
                         0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f, 1.0f, 1.0f,
                        -0.5f,-0.5f, 0.5f, 0.0f,-1.0f, 0.0f, 0.0f, 1.0f,
                        -0.5f,-0.5f,-0.5f, 0.0f,-1.0f, 0.0f, 0.0f, 0.0f,
                    // Top
                    //  |    Position     |     Normal     |    UV     |
                         0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                        -0.5f, 0.5f,-0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                         0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                    // Back
                    //  |    Position     |     Normal     |    UV     |
                         0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 1.0f, 0.0f,
                        -0.5f,-0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 0.0f, 0.0f,
                        -0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 0.0f, 1.0f,
                         0.5f, 0.5f,-0.5f, 0.0f, 0.0f,-1.0f, 1.0f, 1.0f,
                    // Front
                    //  |    Position     |     Normal     |    UV     |
                         0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                         0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                        -0.5f,-0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f
                    };
                }

                indices =
                {
                // Left
                    0, 1, 2,
                    2, 3, 0,
                // Right
                    4, 5, 6,
                    6, 7, 4,
                // Bottom
                    8, 9, 10,
                    10, 11, 8,
                // Top
                    12, 13, 14,
                    14, 15, 12,
                // Back
                    16, 17, 18,
                    18, 19, 16,
                // Front
                    20, 21, 22,
                    22, 23, 20
                };
            }
        };
    }

    unsigned int generate(bool cubemapped);
};