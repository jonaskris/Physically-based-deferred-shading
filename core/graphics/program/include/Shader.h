#pragma once

#include <string>

#include <glad/glad.h>

#include <Defines.h>

namespace graphics
{
    class Shader
    {
    private:
        GLuint id;
        defines::ShaderType type;

    public:
        Shader(const std::string& shaderCode, defines::ShaderType type);
        static Shader loadShader(const std::string& shaderPath, defines::ShaderType type);

        defines::ShaderType getType();
        GLuint getId() const;
    };
}