#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <glad/glad.h>
#include <Shader.h>
#include <Vec2.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>

namespace graphics
{
    class Program
    {
    private:
        GLuint programId;
        bool linkedSuccessfully = false;
        bool validatedSuccessfully = false;

    public:
        Program(const std::vector<std::pair<std::string, Shader::Type>>& shaderPaths);

        GLuint getProgramId() const;
        bool getLinkedSuccessfully() const;
        bool getValidatedSuccessfully() const;

        void enable() const;
        void disable() const;

        GLint getUniformLocation(const GLchar* name);
        void setUniform1f(const GLchar* name, float scalar);
        void setUniformVec2f(const GLchar* name, const math::vec2& vector);
        void setUniformVec3f(const GLchar* name, const math::vec3& vector);
        void setUniformVec4f(const GLchar* name, const math::vec4& vector);
        void setUniformMat4f(const GLchar* name, const math::mat4& matrix);

        friend std::ostream& operator<<(std::ostream& out, const Program& program);
    };
}