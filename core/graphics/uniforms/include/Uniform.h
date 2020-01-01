#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vec2.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>

#include <Texture.h>
#include <Transform.h>

namespace Uniform
{
    void setTexture2D(GLuint programId, const std::string& name, GLuint textureId);
    void setCubemap(GLuint programId, const std::string& name, GLuint textureId);
    void setFloat(GLuint programId, const std::string& name, float f);
    void setVec2(GLuint programId, const std::string& name, const math::Vec2& v);
    void setVec3(GLuint programId, const std::string& name, const math::Vec3& v);
    void setVec4(GLuint programId, const std::string& name, const math::Vec4& v);
    void setMat4(GLuint programId, const std::string& name, const math::Mat4& m);
    void setTransform(GLuint programId, const std::string& name, math::Transform& t);
};

//class Uniform
//{
//protected:
//    std::string name;
//
//public:
//    Uniform(const std::string& name) : name(name) {};
//    virtual void set(GLuint programId) = 0;
//};
//
//class UniformTexture2D : public Uniform
//{
//protected:
//    graphics::Texture2D* texture;
//
//public:
//    UniformTexture2D(const std::string& name, graphics::Texture2D* texture) : Uniform(name), texture(texture) {};
//    void set(GLuint programId) override;
//};
//
//class UniformTextureCubemap : public Uniform
//{
//protected:
//    graphics::TextureCubemap* texture;
//
//public:
//    UniformTextureCubemap(const std::string& name, graphics::TextureCubemap* texture) : Uniform(name), texture(texture) {};
//    void set(GLuint programId) override;
//};
//
//class Uniform1f : public Uniform
//{
//protected:
//    float scalar;
//
//public:
//    Uniform1f(const std::string& name, float scalar) : Uniform(name), scalar(scalar) {};
//    void set(GLuint programId) override;
//    void setScalar(float scalar) { this->scalar = scalar; }
//};
//
//class UniformVec2f : public Uniform
//{
//protected:
//    math::Vec2 vector;
//
//public:
//    UniformVec2f(const std::string& name, const math::Vec2& vector) : Uniform(name), vector(vector) {};
//    void set(GLuint programId) override;
//    void setVector(const math::Vec2& vector) { this->vector = vector; }
//};
//
//class UniformVec3f : public Uniform
//{
//protected:
//    math::Vec3 vector;
//
//public:
//    UniformVec3f(const std::string& name, const math::Vec3& vector) : Uniform(name), vector(vector) {};
//    void set(GLuint programId) override;
//    void setVector(const math::Vec3& vector) { this->vector = vector; }
//}; 
//
//class UniformVec4f : public Uniform
//{
//protected:
//    math::Vec4 vector;
//
//public:
//    UniformVec4f(const std::string& name, const math::Vec4& vector) : Uniform(name), vector(vector) {};
//    void set(GLuint programId) override;
//    void setVector(const math::Vec4& vector) { this->vector = vector; }
//};
//
//class UniformMat4f : public Uniform
//{
//protected:
//    math::Mat4 matrix;
//    
//public:
//    UniformMat4f(const std::string& name) : Uniform(name) {};
//    UniformMat4f(const std::string& name, const math::Mat4& matrix) : Uniform(name), matrix(matrix) {};
//    void set(GLuint programId) override;
//    void setMatrix(const math::Mat4& matrix) { this->matrix = matrix; }
//};
//
//class UniformTransform : public Uniform
//{
//protected:
//    math::Transform transform;
//    
//public:
//    UniformTransform(const std::string& name) : Uniform(name) {};
//    UniformTransform(const std::string& name, const math::Transform& transform) : Uniform(name), transform(transform) {};
//    void set(GLuint programId) override;
//    void setTransform(const math::Transform& transform) { this->transform = transform; }
//};