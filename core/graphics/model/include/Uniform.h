#pragma once

#include <string>
#include <Vec2.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>
#include <glad/glad.h>


class Uniform
{
protected:
    std::string name;

public:
    Uniform(const std::string& name) : name(name) {};

    virtual void set(GLuint programId) const = 0;
};

class Uniform1f : public Uniform
{
protected:
    float scalar;

public:
    Uniform1f(const std::string& name, float scalar) : Uniform(name), scalar(scalar) {};

    void set(GLuint programId) const override;
    void setScalar(float scalar) { this->scalar = scalar; }
};

class UniformVec2f : public Uniform
{
protected:
    math::vec2 vector;

public:
    UniformVec2f(const std::string& name, const math::vec2& vector) : Uniform(name), vector(vector) {};

    void set(GLuint programId) const override;
    void setVector(const math::vec2& vector) { this->vector = vector; }
};
class UniformVec3f : public Uniform
{
protected:
    math::vec3 vector;

public:
    UniformVec3f(const std::string& name, const math::vec3& vector) : Uniform(name), vector(vector) {};

    void set(GLuint programId) const override;
    void setVector(const math::vec3& vector) { this->vector = vector; }
}; 

class UniformVec4f : public Uniform
{
protected:
    math::vec4 vector;

public:
    UniformVec4f(const std::string& name, const math::vec4& vector) : Uniform(name), vector(vector) {};

    void set(GLuint programId) const override;
    void setVector(const math::vec4& vector) { this->vector = vector; }
};

class UniformMat4f : public Uniform
{
protected:
    math::mat4 matrix;

public:
    UniformMat4f(const std::string& name, const math::mat4& matrix) : Uniform(name), matrix(matrix) {};

    void set(GLuint programId) const override;
    void setMatrix(const math::mat4& matrix) { this->matrix = matrix; }
}; 