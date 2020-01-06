#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace graphics
{
    class Buffer
    {
    public:
        enum Type { POSITION, NORMAL, ALBEDO, DEPTH, ROUGHNESS, METALNESS };
    
    private:
        GLuint XBO = 0;
        Type type;
    
    public:
        Buffer(size_t width, size_t height, Type type) : type(type)
        {
            switch(type)
            {
                case Type::POSITION:
                case Type::NORMAL:
                case Type::ALBEDO:
                    glGenTextures(1, &XBO);
                    glBindTexture(GL_TEXTURE_2D, XBO);

                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, NULL);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    break;
                case Type::METALNESS:
                case Type::ROUGHNESS:
                    glGenTextures(1, &XBO);
                    glBindTexture(GL_TEXTURE_2D, XBO);

                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_FLOAT, NULL);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glBindTexture(GL_TEXTURE_2D, 0);
                    break;

                case Type::DEPTH:
                    glGenRenderbuffers(1, &XBO);
                    glBindRenderbuffer(GL_RENDERBUFFER, XBO);
                    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
                    glBindRenderbuffer(GL_RENDERBUFFER, 0);
                    break;
            }
        }

        GLuint getId() const { return XBO; }
    };

    class Framebuffer
    {
    private:
        GLuint FBO;

    public:
        union
        {
            Buffer* buffers[6];
            struct
            {
                Buffer* position;
                Buffer* normal;
                Buffer* albedo;
                Buffer* roughness;
                Buffer* metalness;
                Buffer* depth;
            };
        };

        Framebuffer(size_t width, size_t height)
        {
            glGenFramebuffers(1, &FBO);
            glBindFramebuffer(GL_FRAMEBUFFER, FBO);

            position = new Buffer(width, height, Buffer::Type::POSITION);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, position->getId(), 0);

            normal = new Buffer(width, height, Buffer::Type::NORMAL);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normal->getId(), 0);

            albedo = new Buffer(width, height, Buffer::Type::ALBEDO);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, albedo->getId(), 0);

            roughness = new Buffer(width, height, Buffer::Type::ROUGHNESS);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, roughness->getId(), 0);

            metalness = new Buffer(width, height, Buffer::Type::METALNESS);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, metalness->getId(), 0);

            depth = new Buffer(width, height, Buffer::Type::DEPTH);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth->getId());

            unsigned int attachments[5] = {
                GL_COLOR_ATTACHMENT0,
                GL_COLOR_ATTACHMENT1,
                GL_COLOR_ATTACHMENT2,
                GL_COLOR_ATTACHMENT3,
                GL_COLOR_ATTACHMENT4
            };

            glDrawBuffers(5, attachments);

            if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            {
                std::cout << "Framebuffer not complete!" << std::endl;
                std::cin.get();
            }

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        };

        ~Framebuffer() { glDeleteFramebuffers(1, &FBO); for(size_t i = 0; i <= 5; i++) delete buffers[i]; };

        void bind() { glBindFramebuffer(GL_FRAMEBUFFER, FBO); }
        void unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

        GLuint getId() const { return FBO; }
    };
}