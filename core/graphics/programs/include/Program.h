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
    Program(std::vector<Shader*>&& shaders);
    ~Program();

    // Prevent copying and moving (Because destructor invalidates program handle).
    Program(const Program& program) = delete;
    Program& operator=(const Program& program) = delete;
    Program(Program&& program) = delete;
    Program& operator=(Program&& program) = delete;

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