#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <glad/glad.h>

#include <Program.h>
#include <Shader.h>

namespace graphics
{
    Program::Program(const std::vector<std::pair<std::string, Shader::Type>>& shaderPaths)
    {
        std::vector<Shader> shaders;

        // Create and compile shaders
        for(auto& shaderPath : shaderPaths)
            shaders.emplace_back(shaderPath.first, shaderPath.second);

        // Check shaders compiled successfully
        for(auto& shader : shaders)
            if(!shader.getCompiledSuccessfully())
                return; // linkedSuccessfully/validatedSuccessfully false by default

        programId = glCreateProgram();

        for(auto& shader : shaders)
            glAttachShader(programId, shader.getShaderId());

        glLinkProgram(programId);

        GLint linkResult;
        glGetProgramiv(programId, GL_LINK_STATUS, &linkResult);
        if(linkResult == GL_FALSE)
        {
            std::cout << "Failed to link program!" << std::endl;
            GLint logLength;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<char> logVec(logLength);
            glGetProgramInfoLog(programId, logLength, &logLength, &logVec[0]);

            std::string log(logVec.begin(), logVec.end());
            std::cout << log << std::endl;

            glDeleteProgram(programId);

            return; // linkedSuccessfully/validatedSuccessfully false by default
        }
        linkedSuccessfully = true;

        glValidateProgram(programId);

        GLint validateResult;
        glGetProgramiv(programId, GL_VALIDATE_STATUS, &validateResult);
        if(validateResult == GL_FALSE)
        {
            GLint logLength;
            glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

            std::vector<char> logVec(logLength);
            glGetProgramInfoLog(programId, logLength, &logLength, &logVec[0]);
            
            std::string log(logVec.begin(), logVec.end());
            std::cout << log << std::endl;

            glDeleteProgram(programId);

            return; // validatedSuccessfully false by default
        }
        validatedSuccessfully = true;
    }

    GLuint Program::getProgramId() const
    {
        return programId;
    }

    bool Program::getLinkedSuccessfully() const
    {
        return linkedSuccessfully;
    }

    bool Program::getValidatedSuccessfully() const
    {
        return validatedSuccessfully;
    }

    std::ostream& operator<<(std::ostream& out, const Program& program)
    {
        out << "Program: linkedSuccessfully: " << (program.getLinkedSuccessfully() ? "true":"false") << ", validatedSuccessfully: " << (program.getValidatedSuccessfully() ? "true":"false");
    }
}