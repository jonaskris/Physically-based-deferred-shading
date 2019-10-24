#include <string>
#include <vector>
#include <glad/glad.h>
#include <Sampler.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


Sampler::~Sampler()
{
    glDeleteTextures(1, &samplerId);
}

GLuint Sampler::getSamplerId() { return samplerId; }

Sampler2D::Sampler2D(const std::string& file)
{
    glGenTextures(1, &samplerId);
    glBindTexture(GL_TEXTURE_2D, samplerId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height;
    unsigned char* pixels = stbi_load((char* const)file.c_str(), &width, &height, 0, STBI_rgb_alpha);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    stbi_image_free(pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Sampler2D::set() const
{

}


Sampler3D::Sampler3D(const std::string& all)
{
    glGenTextures(1, &samplerId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, samplerId);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    int width, height;
    unsigned char* pixels = stbi_load((char* const)all.c_str(), &width, &height, 0, STBI_rgb_alpha);
    
    for(size_t i = 0; i < 6; i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);            
    
    stbi_image_free(pixels);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Sampler3D::Sampler3D(const std::string& left, const std::string& right, const std::string& back, const std::string& front, const std::string& top, const std::string& bottom)
{
    std::vector<std::string> sides = { left, right, back, front, top, bottom };
    glGenTextures(1, &samplerId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, samplerId);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    for(size_t i = 0; i < 6; i++)
    {
        int width, height;
        unsigned char* pixels = stbi_load((char* const)sides[i].c_str(), &width, &height, 0, STBI_rgb_alpha);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        
        stbi_image_free(pixels);
    }
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Sampler3D::set() const
{
    
}