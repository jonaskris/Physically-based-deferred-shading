#pragma once

#include <string>
#include <vector>

#include <glad/glad.h>

#include <Defines.h>

#include <Image.h>

namespace graphics
{   
    namespace
    {
        GLenum formatFromChannels(int channels)
        {
            GLenum format;
            switch(channels)
            {
                case 1:
                    format = GL_R;
                    break;
                case 2:
                    format = GL_RG;
                    break;
                case 3:
                    format = GL_RGB;
                    break;
                case 4:
                    format = GL_RGBA;
                    break;
            };

            return format;
        }
    }

    class Texture
    {
    private:
        defines::SamplerType samplerType;

    protected:
        GLuint textureId;
        GLuint width, height;

        Texture(defines::SamplerType samplerType) : samplerType(samplerType)
        {
            glGenTextures(1, &textureId);
        }

    public:
        Texture(defines::SamplerType samplerType, GLuint textureId, GLuint width, GLuint height) : samplerType(samplerType), textureId(textureId), width(width), height(height) {}

        GLuint getTextureId() const { return textureId; }
        defines::SamplerType getSamplerType() const { return samplerType; }
        GLuint getWidth() const { return width; }
        GLuint getHeight() const { return height; }
    };

    class Texture2D : public Texture
    {
    public:
        Texture2D(const Source& imageSource) : Texture(defines::SamplerType::SAMPLER2D)
        {
            Image image(imageSource);
            width = image.getWidth();
            height = image.getHeight();

            GLenum format = formatFromChannels(image.getChannels());

            glBindTexture(GL_TEXTURE_2D, textureId);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image.getPixels());
            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);
        }
    };

    class TextureCubemap : public Texture
    {
    public:
        TextureCubemap(const Source& imageSource) : Texture(defines::SamplerType::SAMPLERCUBE)
        {
            Image image(imageSource);
            this->width = image.getWidth();
            this->height = image.getHeight();

            GLenum format = formatFromChannels(image.getChannels());

            if(width != height)
                throw std::runtime_error("Failed to load TextureCubemap, image not square!");
                
            glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            for(size_t i = 0; i < 6; i++)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image.getPixels());            

            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);  
        }     

        /*
            Images should be in order: Right, left, top, bottom, front, back
        */
        TextureCubemap(const std::vector<Source>& imageSources) : Texture(defines::SamplerType::SAMPLERCUBE)
        {
            std::vector<Image> images;
            images.reserve(imageSources.size());

            for(const Source& source : imageSources)
                images.emplace_back(source);

            this->width = images.front().getWidth();
            this->height = images.front().getHeight();

            if(width != height)
                throw std::runtime_error("Failed to load TextureCubemap, image not square!");

            if(images.size() != 6)
                throw std::runtime_error("Failed to load TextureCubemap, images.size() != 6!");

            for(size_t i = 1; i < images.size(); i++)
                if(images[i].getWidth() != width || images[i].getHeight() != height)
                    throw std::runtime_error("Failed to load TextureCubemap, images have different sizes!");
                else if(images[i].getChannels() != images.front().getChannels())
                    throw std::runtime_error("Failed to load TextureCubemap, images have different number of channels!");

            GLenum format = formatFromChannels(images.front().getChannels());

            glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            // Right, left, Up, Down, back, front
            for(size_t i = 0; i < 6; i++)
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, images[i].getWidth(), images[i].getWidth(), 0, format, GL_UNSIGNED_BYTE, images[i].getPixels());        

            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }
    };
}