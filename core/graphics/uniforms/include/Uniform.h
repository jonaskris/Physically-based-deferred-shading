#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vec2.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>
#include <Sampler.h>


class Uniform
{
protected:
    std::string name;

public:
    Uniform(const std::string& name) : name(name) {};
    virtual void set(GLuint programId) const = 0;
};

class UniformSampler2D : public Uniform
{
protected:
    Sampler2D* sampler;

public:
    UniformSampler2D() : Uniform("NULL"), sampler(nullptr) {};
    UniformSampler2D(const std::string& name, Sampler2D* sampler) : Uniform(name), sampler(sampler) {};
    void set(GLuint programId) const override;
};

class UniformSampler3D : public Uniform
{
protected:
    Sampler3D* sampler;

public:
    UniformSampler3D() : Uniform("NULL"), sampler(nullptr) {};
    UniformSampler3D(const std::string& name, Sampler3D* sampler) : Uniform(name), sampler(sampler) {};
    void set(GLuint programId) const override;
};

class Uniform1f : public Uniform
{
protected:
    float scalar;

public:
    Uniform1f() : Uniform("NULL"), scalar(0.0f) {}
    Uniform1f(const std::string& name, float scalar) : Uniform(name), scalar(scalar) {};
    void set(GLuint programId) const override;
    void setScalar(float scalar) { this->scalar = scalar; }
};

class UniformVec2f : public Uniform
{
protected:
    math::Vec2 vector;

public:
    UniformVec2f() : Uniform("NULL"), vector({}) {}
    UniformVec2f(const std::string& name, const math::Vec2& vector) : Uniform(name), vector(vector) {};
    void set(GLuint programId) const override;
    void setVector(const math::Vec2& vector) { this->vector = vector; }
};

class UniformVec3f : public Uniform
{
protected:
    math::Vec3 vector;

public:
    UniformVec3f() : Uniform("NULL"), vector({}) {}
    UniformVec3f(const std::string& name, const math::Vec3& vector) : Uniform(name), vector(vector) {};
    void set(GLuint programId) const override;
    void setVector(const math::Vec3& vector) { this->vector = vector; }
}; 

class UniformVec4f : public Uniform
{
protected:
    math::Vec4 vector;

public:
    UniformVec4f() : Uniform("NULL"), vector({}) {}
    UniformVec4f(const std::string& name, const math::Vec4& vector) : Uniform(name), vector(vector) {};
    void set(GLuint programId) const override;
    void setVector(const math::Vec4& vector) { this->vector = vector; }
};

class UniformMat4f : public Uniform
{
protected:
    math::Mat4 matrix;
    
public:
    UniformMat4f() : Uniform("NULL"), matrix({}) {}
    UniformMat4f(const std::string& name, const math::Mat4& matrix) : Uniform(name), matrix(matrix) {};
    void set(GLuint programId) const override;
    void setMatrix(const math::Mat4& matrix) { this->matrix = matrix; }
}; 