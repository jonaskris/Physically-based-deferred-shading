#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader.h>
#include <Vec2.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>

class Program
{
private:
    GLuint programId;
    bool linkedSuccessfully = false;
    bool validatedSuccessfully = false;

public:
    Program(std::vector<std::pair<std::string, Shader::Type>> shaderPaths);
    Program(std::vector<Shader*> shaders);
    ~Program();

    // Prevent copying and moving (Because destructor invalidates program handle).
    Program(const Program& program) = delete;
    Program& operator=(const Program& program) = delete;
    Program(Program&& program) = delete;
    Program& operator=(Program&& program) = delete;

    GLuint getProgramId() const;
    bool getLinkedSuccessfully() const;
    void validate();
    bool getValidatedSuccessfully() const;

    void enable() const;
    void disable() const;
    
    GLint getUniformLocation(const GLchar* name);
    void setUniform1f(const GLchar* name, float scalar);
    void setUniformVec2f(const GLchar* name, const math::Vec2& vector);
    void setUniformVec3f(const GLchar* name, const math::Vec3& vector);
    void setUniformVec4f(const GLchar* name, const math::Vec4& vector);
    void setUniformMat4f(const GLchar* name, const math::Mat4& matrix);

    friend std::ostream& operator<<(std::ostream& out, const Program& program);
};