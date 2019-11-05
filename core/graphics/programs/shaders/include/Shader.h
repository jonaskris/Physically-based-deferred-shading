#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Shader
{
public:
    enum Type { VERTEX, FRAGMENT, GEOMETRY, TESS_EVALUATION, TESS_CONTROL, COMPUTE };
    Type type;
    
    GLuint shaderId;
    bool compiledSuccessfully = false;

public:
    Shader(const std::string& file, Shader::Type type);
    ~Shader();
    
    // Prevent copying and moving (Because destructor invalidates shader handle).
    Shader(const Shader& shader) = delete;
    Shader& operator=(const Shader& shader) = delete;
    Shader(Shader&& shader) = delete;
    Shader& operator=(Shader&& shader) = delete;

    GLuint getShaderId() const;
    bool getCompiledSuccessfully() const;

    friend std::ostream& operator<<(std::ostream& out, const Shader& shader);
};
