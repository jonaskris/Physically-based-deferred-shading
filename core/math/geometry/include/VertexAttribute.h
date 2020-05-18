#pragma once

#include <glad/glad.h>

#include <Defines.h>

namespace math::geometry
{
    struct VertexAttribute
    {
        defines::VertexAttribute vertexAttribute; // Type of attribute (Position, normal, uv, color...)
        GLuint index;
        defines::NumeralType numeralType; // Nr of components
        GLenum type;    // Float, double, int...
        GLboolean normalized;
        GLsizei stride;
        const void* offset;
    };
}