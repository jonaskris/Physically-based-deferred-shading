#pragma once

#include <map>

#include <glad/glad.h>

namespace graphics
{
    struct VertexAttribute
    {
        GLuint index;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLsizei stride;
        const void* offset;
    };
}