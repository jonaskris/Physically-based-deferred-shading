#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Sampler.h>

#include <Image.h>

Sampler::~Sampler()
{
    glDeleteTextures(1, &samplerId);
}

GLuint Sampler::getSamplerId() { return samplerId; }

Sampler2D::Sampler2D(const Image& image)
{
    glGenTextures(1, &samplerId);
    glBindTexture(GL_TEXTURE_2D, samplerId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixels());

    glBindTexture(GL_TEXTURE_2D, 0);
}

Sampler3D::Sampler3D(const Image& all)
{
    glGenTextures(1, &samplerId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, samplerId);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    for(size_t i = 0; i < 6; i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, all.getWidth(), all.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, all.getPixels());            
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Sampler3D::Sampler3D(const Image& left, const Image& right, const Image& back, const Image& front, const Image& top, const Image& bottom)
{
    std::vector<Image> sides = { left, right, back, front, top, bottom };
    glGenTextures(1, &samplerId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, samplerId);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    for(size_t i = 0; i < 6; i++)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, sides[i].getWidth(), sides[i].getWidth(), 0, GL_RGBA, GL_UNSIGNED_BYTE, sides[i].getPixels());        
    
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}