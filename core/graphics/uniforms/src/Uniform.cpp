#include <Uniform.h>
#include <string>

#include <glad/glad.h>

#include <Vec2.h>
#include <Vec3.h>
#include <Vec4.h>
#include <Mat4.h>

#include <Texture.h>
#include <Transform.h>
#include <TextureUnitManager.h>

namespace Uniform
{
    void setTexture2D(GLuint programId, const std::string& name, GLuint textureId)
    {
        GLuint textureUnit = TextureUnitManager::requestTextureUnit();
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glUniform1i(glGetUniformLocation(programId, &name[0]), textureUnit);
    }

    void setCubemap(GLuint programId, const std::string& name, GLuint textureId)
    {
        GLuint textureUnit = TextureUnitManager::requestTextureUnit();
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);  
        glUniform1i(glGetUniformLocation(programId, &name[0]), textureUnit);
    }
    
    void setFloat(GLuint programId, const std::string& name, float f)
    {
        glUniform1f(glGetUniformLocation(programId, &name[0]), f);
    }
    
    void setVec2(GLuint programId, const std::string& name, const math::Vec2& v)
    {
        glUniform2f(glGetUniformLocation(programId, &name[0]), v.elements[0], v.elements[1]);
    }
    
    void setVec3(GLuint programId, const std::string& name, const math::Vec3& v)
    {
        glUniform3f(glGetUniformLocation(programId, &name[0]), v.elements[0], v.elements[1], v.elements[2]);
    }
    
    void setVec4(GLuint programId, const std::string& name, const math::Vec4& v)
    {
        glUniform4f(glGetUniformLocation(programId, &name[0]), v.elements[0], v.elements[1], v.elements[2], v.elements[3]);
    }
    
    void setMat4(GLuint programId, const std::string& name, const math::Mat4& m)
    {
        glUniformMatrix4fv(glGetUniformLocation(programId, &name[0]), 1, GL_FALSE, m.elements);
    }

    void setTransform(GLuint programId, const std::string& name, math::Transform& t)
    {
        setMat4(programId, name, t.toMatrix());
    }
};

//
//void UniformTexture2D::set(GLuint programId)
//{
//    size_t textureId = texture->getTextureId();
//    //std::cout << "Set Sampler2D uniform " << name << ", " << samplerId << std::endl;
//    glBindTexture(GL_TEXTURE_2D, textureId);
//    glUniform1i(glGetUniformLocation(programId, &name[0]), TextureUnitManager::requestTextureUnit());
//}
//
//void UniformTextureCubemap::set(GLuint programId)
//{
//    size_t textureId = texture->getTextureId();
//    //std::cout << "Set Sampler3D uniform " << name << ", " << samplerId << std::endl;
//    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);  
//    glUniform1i(glGetUniformLocation(programId, &name[0]), TextureUnitManager::requestTextureUnit());
//}
//
//void Uniform1f::set(GLuint programId)
//{
//    glUniform1f(glGetUniformLocation(programId, &name[0]), scalar);
//}
//
//void UniformVec2f::set(GLuint programId)
//{
//    glUniform2f(glGetUniformLocation(programId, &name[0]), vector.elements[0], vector.elements[1]);
//}
//
//void UniformVec3f::set(GLuint programId)
//{
//    glUniform3f(glGetUniformLocation(programId, &name[0]), vector.elements[0], vector.elements[1], vector.elements[2]);
//}
//
//void UniformVec4f::set(GLuint programId)
//{
//    glUniform4f(glGetUniformLocation(programId, &name[0]), vector.elements[0], vector.elements[1], vector.elements[2], vector.elements[3]);
//}
//
//void UniformMat4f::set(GLuint programId)
//{
//    //std::cout << "Set Mat4 uniform " << name << std::endl << matrix << std::endl << std::endl;
//    glUniformMatrix4fv(glGetUniformLocation(programId, &name[0]), 1, GL_FALSE, matrix.elements);
//}
//
//void UniformTransform::set(GLuint programId)
//{
//    //std::cout << "Set Transform uniform " << name << std::endl << transform << std::endl << std::endl;
//    glUniformMatrix4fv(glGetUniformLocation(programId, &name[0]), 1, GL_FALSE, transform.toMatrix().elements);
//}