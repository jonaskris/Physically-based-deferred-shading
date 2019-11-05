#pragma once
#include <Uniform.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Program;

class Material
{
private:
    Uniform* albedo;

public:
    Material(Uniform* albedo) : albedo(albedo) {}

    void set(GLuint programId);
};