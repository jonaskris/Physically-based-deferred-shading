#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Uniform.h>

class Program;

class Material
{
private:
    Uniform* albedo;

public:
    Material(Uniform* albedo) : albedo(albedo) {}

    void set(GLuint programId);
};