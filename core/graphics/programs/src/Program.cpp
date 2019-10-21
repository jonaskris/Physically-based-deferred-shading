#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <glad/glad.h>

#include <Program.h>
#include <Shader.h>
#include <Vec2.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>

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

    GLint Program::getUniformLocation(const GLchar* name)
    {
        return glGetUniformLocation(programId, name);
    }

    void Program::setUniform1f(const GLchar* name, float scalar)
    {
        glUniform1f(getUniformLocation(name), scalar);
    }

    void Program::setUniform1i(const GLchar* name, int scalar)
    {
        glUniform1i(getUniformLocation(name), scalar);
    }

    void Program::setUniform2f(const GLchar* name, const math::vec2& vector)
    {
        glUniform2f(getUniformLocation(name), vector.x, vector.y);
    }

    void Program::setUniform3f(const GLchar* name, const math::vec3& vector)
    {
        glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
    }

    void Program::setUniform4f(const GLchar* name, const math::vec4& vector)
    {
        glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
    }

    void Program::setUniformMat4(const GLchar* name, const math::mat4& matrix)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
    }

    std::ostream& operator<<(std::ostream& out, const Program& program)
    {
        out << "Program: linkedSuccessfully: " << (program.getLinkedSuccessfully() ? "true":"false") << ", validatedSuccessfully: " << (program.getValidatedSuccessfully() ? "true":"false");
    }
}