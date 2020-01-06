#pragma once

#include <string>

#include <glad/glad.h>

#include <Image.h>
#include <TextureUnitManager.h>

namespace graphics
{   
    class Texture
    {
    protected:
        GLuint textureId;       

    public:
        GLuint getTextureId() const { return textureId; }
    };

    class Texture2D : public Texture
    {
    public:
        Texture2D(const Image& image, GLenum channels = GL_RGB)
        {
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
            glTexImage2D(GL_TEXTURE_2D, 0, channels, image.getWidth(), image.getHeight(), 0, channels, GL_UNSIGNED_BYTE, image.getPixels());

            glBindTexture(GL_TEXTURE_2D, 0);
        }
    };

    class TextureCubemap : public Texture
    {
    public:
        TextureCubemap(Image& image, GLenum channels = GL_RGB)
        {
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            for(size_t i = 0; i < 6; i++)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, channels, image.getWidth(), image.getHeight(), 0, channels, GL_UNSIGNED_BYTE, image.getPixels());            

            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);  
        }

        TextureCubemap(const Image& left, const Image& right, const Image& back, const Image& front, const Image& top, const Image& bottom, GLenum channels = GL_RGB)
        {
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            // Right, left, Up, Down, back, front

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, channels, right.getWidth(), right.getWidth(), 0, channels, GL_UNSIGNED_BYTE, right.getPixels());        
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, channels, left.getWidth(), left.getWidth(), 0, channels, GL_UNSIGNED_BYTE, left.getPixels());        
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, channels, top.getWidth(), top.getWidth(), 0, channels, GL_UNSIGNED_BYTE, top.getPixels());                    
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, channels, bottom.getWidth(), bottom.getWidth(), 0, channels, GL_UNSIGNED_BYTE, bottom.getPixels());        
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, channels, back.getWidth(), back.getWidth(), 0, channels, GL_UNSIGNED_BYTE, back.getPixels());        
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, channels, front.getWidth(), front.getWidth(), 0, channels, GL_UNSIGNED_BYTE, front.getPixels());        
    
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }
    };
}