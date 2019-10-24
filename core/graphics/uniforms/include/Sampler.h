#pragma once

#include <string>
#include <glad/glad.h>

class Sampler 
{
protected:
    GLuint samplerId;

public:
    ~Sampler();

    virtual void set() const = 0;
    GLuint getSamplerId();
};

class Sampler2D : public Sampler
{
public:
    Sampler2D(const std::string& file);

    void set() const override;
};

class Sampler3D : public Sampler
{
public:
    Sampler3D(const std::string& all);
    Sampler3D(const std::string& left, const std::string& right, const std::string& back, const std::string& front, const std::string& top, const std::string& bottom);
    
    void set() const override;
};