#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Shader.h>

Shader::Shader(const std::string& filepath, Shader::Type type) : type(type)
{
    if(type == Shader::Type::VERTEX) shaderId = glCreateShader(GL_VERTEX_SHADER);
    else if(type == Shader::Type::FRAGMENT) shaderId = glCreateShader(GL_FRAGMENT_SHADER);
    else if(type == Shader::Type::GEOMETRY) shaderId = glCreateShader(GL_GEOMETRY_SHADER);
    else if(type == Shader::Type::TESS_EVALUATION) shaderId = glCreateShader(GL_TESS_EVALUATION_SHADER);
    else if(type == Shader::Type::TESS_CONTROL) shaderId = glCreateShader(GL_TESS_CONTROL_SHADER);
    else if(type == Shader::Type::COMPUTE) shaderId = glCreateShader(GL_COMPUTE_SHADER);

    std::ifstream file(filepath);
    if(!file.is_open())
    {
        std::cout << "Failed to open file: " << filepath << std::endl;
        return; // compiledSuccessfully false by default
    }

    std::string content( 
        (std::istreambuf_iterator<char>(file)),
        (std::istreambuf_iterator<char>())
    );
    file.close();

    const char* c_str = content.c_str();
    glShaderSource(shaderId, 1, &c_str, NULL);
    glCompileShader(shaderId);

    GLint compileResult;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileResult);
    if(compileResult == GL_FALSE)
    {
        std::cout << "Failed to compile shader: " << filepath << std::endl;
        GLint logLength;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
        
        std::vector<char> logVec(logLength);
        glGetShaderInfoLog(shaderId, logLength, &logLength, &logVec[0]);
        std::string log(logVec.begin(), logVec.end());
        std::cout << log << std::endl;
        glDeleteShader(shaderId);
        return; // compiledSuccessfully false by default
    }
    compiledSuccessfully = true;
};

Shader::~Shader()
{
    glDeleteShader(shaderId);
}

GLuint Shader::getShaderId() const 
{ 
    return shaderId; 
}

bool Shader::getCompiledSuccessfully() const
{
    return compiledSuccessfully;
}

std::ostream& operator<<(std::ostream& out, const Shader& shader)
{
    out << "Shaderid:  " << shader.shaderId << ", compiledSuccessfully: " << (shader.getCompiledSuccessfully() ? "true":"false") << ", type: " << shader.type;
    return out;
}