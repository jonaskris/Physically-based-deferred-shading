#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>

namespace graphics
{
    class Shader
    {
    public:
        enum Type { VERTEX, FRAGMENT, GEOMETRY, TESS_EVALUATION, TESS_CONTROL, COMPUTE };

        GLuint shaderId;
        bool compiledSuccessfully = false;

    public:
        Shader(const std::string& file, Shader::Type type);
        ~Shader();

        GLuint getShaderId() const;
        bool getCompiledSuccessfully() const;

        friend std::ostream& operator<<(std::ostream& out, const Shader& shader);
    };
}