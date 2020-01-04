#pragma once

#include <glad/glad.h>

namespace graphics
{
    class Material
    {
    private:
        unsigned int albedo;

    public:
        Material(unsigned int albedo);

        void set(GLuint programId);
    };
}