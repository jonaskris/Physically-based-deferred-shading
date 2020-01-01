#pragma once

#include <string>

#include <glad/glad.h>

#include <Image.h>
#include <TextureUnitManager.h>

namespace graphics
{
    namespace
    {
        // Converts nr of channels to GLenum
        GLenum toFormat(unsigned int channels)
        {
            switch(channels)
            {
                case 1:
                    return GL_RED;
                    break;
                case 2:
                    return GL_RG;
                    break;
                case 3:
                    return GL_RGB;
                    break;
                case 4:
                    return GL_RGBA;
                    break;
                default:
                    std::cout << "Failed to convert channels in image to GLenum!" << std::endl;
                    return GL_RGBA;
            }
        }
    }
    
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
        Texture2D(const Image& image)
        {
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_2D, textureId);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
            GLenum format = toFormat(image.getChannels());
            glTexImage2D(GL_TEXTURE_2D, 0, format, image.getWidth(), image.getHeight(), 0, format, GL_UNSIGNED_BYTE, image.getPixels());

            glBindTexture(GL_TEXTURE_2D, 0);
        }
    };

    class TextureCubemap : public Texture
    {
    public:
        TextureCubemap(Image& image)
        {
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            GLenum format = toFormat(image.getChannels());
            for(size_t i = 0; i < 6; i++)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, image.getWidth(), image.getHeight(), 0, format, GL_UNSIGNED_BYTE, image.getPixels());            

            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);  
        }

        TextureCubemap(const Image& left, const Image& right, const Image& back, const Image& front, const Image& top, const Image& bottom)
        {
            glGenTextures(1, &textureId);
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            
            GLenum leftFormat = toFormat(left.getChannels());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, leftFormat, left.getWidth(), left.getWidth(), 0, leftFormat, GL_UNSIGNED_BYTE, left.getPixels());        
            
            GLenum rightFormat = toFormat(right.getChannels());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, rightFormat, right.getWidth(), right.getWidth(), 0, rightFormat, GL_UNSIGNED_BYTE, right.getPixels());        
            
            GLenum backFormat = toFormat(back.getChannels());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, backFormat, back.getWidth(), back.getWidth(), 0, backFormat, GL_UNSIGNED_BYTE, back.getPixels());        
            
            GLenum frontFormat = toFormat(front.getChannels());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, frontFormat, front.getWidth(), front.getWidth(), 0, frontFormat, GL_UNSIGNED_BYTE, front.getPixels());        
            
            GLenum topFormat = toFormat(top.getChannels());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, topFormat, top.getWidth(), top.getWidth(), 0, topFormat, GL_UNSIGNED_BYTE, top.getPixels());        
            
            GLenum bottomFormat = toFormat(bottom.getChannels());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, bottomFormat, bottom.getWidth(), bottom.getWidth(), 0, bottomFormat, GL_UNSIGNED_BYTE, bottom.getPixels());        
    
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }
    };
}