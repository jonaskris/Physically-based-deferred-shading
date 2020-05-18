#include <Shader.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <glad/glad.h>

namespace graphics
{
    Shader::Shader(const std::string& shaderCode, ShaderType type)
    {        
        if(type == ShaderType::VERTEX) id = glCreateShader(GL_VERTEX_SHADER);
        else if(type == ShaderType::FRAGMENT) id = glCreateShader(GL_FRAGMENT_SHADER);
        else if(type == ShaderType::GEOMETRY) id = glCreateShader(GL_GEOMETRY_SHADER);
        else if(type == ShaderType::TESS_EVALUATION) id = glCreateShader(GL_TESS_EVALUATION_SHADER);
        else if(type == ShaderType::TESS_CONTROL) id = glCreateShader(GL_TESS_CONTROL_SHADER);
        else if(type == ShaderType::COMPUTE) id = glCreateShader(GL_COMPUTE_SHADER);

        // Submit shadercode to OpenGL
        const char* content_c_str = shaderCode.c_str();
        glShaderSource(id, 1, &content_c_str, NULL);
        glCompileShader(id);

        GLint compileResult;
        glGetShaderiv(id, GL_COMPILE_STATUS, &compileResult);
        if(compileResult == GL_FALSE)
        {
            GLint logLength;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<char> logVec(logLength);
            glGetShaderInfoLog(id, logLength, &logLength, &logVec[0]);
            std::string log(logVec.begin(), logVec.end());

            glDeleteShader(id);

            throw std::runtime_error( std::string("Failed to compile shader!\n\tLog: ") + log);
        }
    }

    Shader Shader::loadShader(const std::string& shaderPath, ShaderType type)
    {
        std::ifstream file(shaderPath);
        if(!file.is_open())
            throw std::runtime_error("Failed to open file when creating shader from path!");

        std::string shaderCode( 
            (std::istreambuf_iterator<char>(file)),
            (std::istreambuf_iterator<char>())
        );
        file.close();

        return Shader(shaderCode, type);
    }

    ShaderType Shader::getType() { return type; }
    GLuint Shader::getId() const { return id; }
};