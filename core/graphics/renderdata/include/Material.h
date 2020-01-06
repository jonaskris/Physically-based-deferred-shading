#pragma once

#include <string>

#include <glad/glad.h>

namespace graphics
{
    class Texture;

    class Material
    {
    private:
        unsigned int albedo, roughness, metalness;

    public:
        Material(unsigned int albedo, unsigned int roughness = 0, unsigned int metalness = 0);

        void set(GLuint programId);

        void setAlbedo(GLuint programId, const std::string& name = "albedo") const;
        void setRoughness(GLuint programId, const std::string& name = "roughness") const;
        void setMetalness(GLuint programId, const std::string& name = "metalness") const;
    };
}