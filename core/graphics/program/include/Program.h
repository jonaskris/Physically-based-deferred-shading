#pragma once

#include <vector>

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
        GLuint id;        

    public:
        Program(const std::vector<Shader>& shaders);

        GLuint getId() const;

        void enable() const;
        void disable() const;

        GLint getUniformLocation(const std::string& name);
        void setUniform1b(const std::string& name, bool b);
        void setUniform1i(const std::string& name, int32_t integer);
        void setUniform1ui(const std::string& name, uint32_t uinteger);
        void setUniform1f(const std::string& name, float scalar);
        void setUniformVec2f(const std::string& name, const math::Vec2& vector);
        void setUniformVec3f(const std::string& name, const math::Vec3& vector);
        void setUniformVec4f(const std::string& name, const math::Vec4& vector);
        void setUniformMat4f(const std::string& name, const math::Mat4& matrix);
        void setTexture2D(const std::string& name, GLuint textureId);
        void setCubemap(const std::string& name, GLuint textureId);
    };
}