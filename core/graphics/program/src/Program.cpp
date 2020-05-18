#include <Program.h>

#include <vector>

#include <glad/glad.h>

#include <Shader.h>
#include <TextureUnitManager.h>

#include <Vec2.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>

namespace graphics
{
    Program::Program(const std::vector<Shader>& shaders)
    {        
        // Create program
        id = glCreateProgram();

        for(const Shader& shader : shaders)
            glAttachShader(id, shader.getId());

        glLinkProgram(id);
        GLint linkResult;
        glGetProgramiv(id, GL_LINK_STATUS, &linkResult);
        if(linkResult == GL_FALSE)
        {
            GLint logLength;
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
            std::vector<char> logVec(logLength);
            glGetProgramInfoLog(id, logLength, &logLength, &logVec[0]);
            std::string log(logVec.begin(), logVec.end());

            glDeleteProgram(id);

            throw std::runtime_error( std::string("Failed to link program!\n\tLog: ") + log );
        }
    }

    GLuint Program::getId() const { return id; }

    void Program::enable() const
    {
        glUseProgram(id);
    }

    void Program::disable() const
    {
        glUseProgram(0);
    }

    GLint Program::getUniformLocation(const std::string& name)
    {
        return glGetUniformLocation(id, &name[0]);
    }

    void Program::setUniform1b(const std::string& name, bool b)
    {
        setUniform1i(name, b ? 1 : 0);
    }

    void Program::setUniform1i(const std::string& name, int32_t integer)
    {
        glUniform1i(getUniformLocation(name), integer);
    }

    void Program::setUniform1ui(const std::string& name, uint32_t uinteger)
    {
        glUniform1ui(getUniformLocation(name), uinteger);
    }

    void Program::setUniform1f(const std::string& name, float scalar)
    {
        glUniform1f(getUniformLocation(name), scalar);
    }

    void Program::setUniformVec2f(const std::string& name, const math::Vec2& vector)
    {
        glUniform2f(getUniformLocation(name), vector.elements[0], vector.elements[1]);
    }

    void Program::setUniformVec3f(const std::string& name, const math::Vec3& vector)
    {
        glUniform3f(getUniformLocation(name), vector.elements[0], vector.elements[1], vector.elements[2]);
    }

    void Program::setUniformVec4f(const std::string& name, const math::Vec4& vector)
    {
        glUniform4f(getUniformLocation(name), vector.elements[0], vector.elements[1], vector.elements[2], vector.elements[3]);
    }

    void Program::setUniformMat4f(const std::string& name, const math::Mat4& matrix)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
    }

    void Program::setTexture2D(const std::string& name, GLuint textureId)
    {
        GLuint textureUnit = TextureUnitManager::requestTextureUnit();
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glUniform1i(getUniformLocation(name), textureUnit);
    }

    void Program::setCubemap(const std::string& name, GLuint textureId)
    {
        GLuint textureUnit = TextureUnitManager::requestTextureUnit();
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);  
        glUniform1i(getUniformLocation(name), textureUnit);
    }
}