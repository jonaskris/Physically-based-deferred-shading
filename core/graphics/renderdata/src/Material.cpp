#include <Material.h>

#include <string>

#include <glad/glad.h>
#include <Texture.h>
#include <RenderData.h>
#include <Uniform.h>
#include <TextureUnitManager.h>

namespace graphics
{
    Material::Material(unsigned int albedo, unsigned int roughness, unsigned int metalness) : albedo(albedo), roughness(roughness), metalness(metalness) {}

    void Material::set(GLuint programId)
    {
        TextureUnitManager::pushContext();

        setAlbedo(programId);
        setRoughness(programId);
        setMetalness(programId);

        TextureUnitManager::popContext();
    }

    void Material::setAlbedo(GLuint programId, const std::string& name) const
    {
        if(albedo)
        {
            Texture* t = RenderData::get<TextureCubemap>(albedo);
            if(t)
                Uniform::setCubemap(programId, name, t->getTextureId());
            else
            {
                t = RenderData::get<Texture2D>(albedo);
                if(t)
                    Uniform::setTexture2D(programId, name, t->getTextureId());
                else
                    std::cout << "Couldent find texture!" << std::endl;
            }
        }
    }

    void Material::setRoughness(GLuint programId, const std::string& name) const
    {
        if(roughness)
        {
            Texture* t = RenderData::get<TextureCubemap>(roughness);
            if(t)
                Uniform::setCubemap(programId, name, t->getTextureId());
            else
            {
                t = RenderData::get<Texture2D>(roughness);
                if(t)
                    Uniform::setTexture2D(programId, name, t->getTextureId());
                else
                    std::cout << "Couldent find texture!" << std::endl;
            }
        }
    }

    void Material::setMetalness(GLuint programId, const std::string& name) const
    {
        if(metalness)
        {
            Texture* t = RenderData::get<TextureCubemap>(metalness);
            if(t)
                Uniform::setCubemap(programId, name, t->getTextureId());
            else
            {
                t = RenderData::get<Texture2D>(metalness);
                if(t)
                    Uniform::setTexture2D(programId, name, t->getTextureId());
                else
                    std::cout << "Couldent find texture!" << std::endl;
            }
        }
    }
}