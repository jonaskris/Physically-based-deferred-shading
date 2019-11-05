#include <Uniform.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <TextureUnitManager.h>

void UniformSampler2D::set(GLuint programId) const
{
    size_t samplerId = sampler->getSamplerId();
    //std::cout << "Set Sampler2D uniform " << name << ", " << samplerId << std::endl;
    glBindTexture(GL_TEXTURE_2D, samplerId);
    glUniform1i(glGetUniformLocation(programId, &name[0]), TextureUnitManager::requestTextureUnit());
}

void UniformSampler3D::set(GLuint programId) const
{
    size_t samplerId = sampler->getSamplerId();
    //std::cout << "Set Sampler3D uniform " << name << ", " << samplerId << std::endl;
    glBindTexture(GL_TEXTURE_CUBE_MAP, samplerId);    
    glUniform1i(glGetUniformLocation(programId, &name[0]), TextureUnitManager::requestTextureUnit());
}

void Uniform1f::set(GLuint programId) const
{
    glUniform1f(glGetUniformLocation(programId, &name[0]), scalar);
}

void UniformVec2f::set(GLuint programId) const
{
    glUniform2f(glGetUniformLocation(programId, &name[0]), vector.x, vector.y);
}

void UniformVec3f::set(GLuint programId) const
{
    glUniform3f(glGetUniformLocation(programId, &name[0]), vector.x, vector.y, vector.z);
}

void UniformVec4f::set(GLuint programId) const
{
    glUniform4f(glGetUniformLocation(programId, &name[0]), vector.x, vector.y, vector.z, vector.w);
}

void UniformMat4f::set(GLuint programId) const
{
    //std::cout << "Set Mat4 uniform " << name << std::endl << matrix << std::endl << std::endl;
    glUniformMatrix4fv(glGetUniformLocation(programId, &name[0]), 1, GL_FALSE, matrix.elements);
}