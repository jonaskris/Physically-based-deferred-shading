#pragma once

#include <cmath>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vertex.h>
#include <Mesh.h>
#include <Vec3.h>

namespace AxisTriplets
{
    Mesh* generate()
    {
        return new Mesh<VertexType>
        (
            {
                Vec3(0.0f, 0.0f, 0.0f),

                Vec3(1.0f, 0.0f, 0.0f),
                Vec3(0.0f, 1.0f, 0.0f),
                Vec3(0.0f, 0.0f, 1.0f),
            }, 
            {
                0, 1, 0, 2, 0, 3
            });
    }
}