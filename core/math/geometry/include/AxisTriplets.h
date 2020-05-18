#pragma once

#include <cmath>
#include <cstdint>

#include <Geometry.h>
#include <VertexAttribute.h>
#include <Vec3.h>

namespace math::geometry
{
    namespace AxisTriplets
    {
        Geometry generate()
        {
            return Geometry(
                {
                //  |    Position   |
                    0.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f
                },
                {
                    // Position
                    VertexAttribute{VertexAttribute::SemanticType::POSITION, 0, 3, GL_FLOAT, true, 3 * sizeof(float), 0},
                },
                {
                    0, 1, 0, 2, 0, 3
                }
            );
        }
    }
}