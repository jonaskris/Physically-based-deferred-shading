#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Mat4.h>

class Node
{
public:
    Node() {}

    virtual void setUniforms(GLuint programid) = 0;
    virtual void draw() const = 0;
};