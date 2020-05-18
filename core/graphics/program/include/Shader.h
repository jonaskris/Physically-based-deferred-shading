#pragma once

#include <string>

#include <glad/glad.h>

namespace graphics
{
    enum class ShaderType { VERTEX, FRAGMENT, GEOMETRY, TESS_EVALUATION, TESS_CONTROL, COMPUTE };

    class Shader
    {
    private:
        GLuint id;
        ShaderType type;

    public:
        Shader(const std::string& shaderCode, ShaderType type);
        static Shader loadShader(const std::string& shaderPath, ShaderType type);

        ShaderType getType();
        GLuint getId() const;
    };
}