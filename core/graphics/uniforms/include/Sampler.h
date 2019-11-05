#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Image;

class Sampler 
{
protected:
    GLuint samplerId;

public:
    ~Sampler();

    GLuint getSamplerId();
};

class Sampler2D : public Sampler
{
public:
    Sampler2D(const Image& image);
};

class Sampler3D : public Sampler
{
public:
    Sampler3D(const Image& image);
    Sampler3D(const Image& left, const Image& right, const Image& back, const Image& front, const Image& top, const Image& bottom);
};