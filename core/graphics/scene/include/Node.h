#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Mat4.h>
#include <Transform.h>

class Node
{
public:
    math::Transform transform;

    Node() {}

    virtual void setUniforms(GLuint programid) = 0;
    virtual void draw() const = 0;
};