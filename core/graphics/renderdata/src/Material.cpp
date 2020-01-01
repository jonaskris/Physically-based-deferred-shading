#include <Material.h>

#include <glad/glad.h>
#include <Texture.h>
#include <RenderData.h>
#include <Uniform.h>
#include <TextureUnitManager.h>

namespace graphics
{
    Material::Material(unsigned int albedo) : albedo(albedo) {}

    void Material::set(GLuint programId)
    {
        TextureUnitManager::pushContext();

        if(albedo)
        {
            Texture* t = RenderData::get<TextureCubemap>(albedo);
            if(t)
                Uniform::setCubemap(programId, "albedo", t->getTextureId());
            else
            {
                t = RenderData::get<Texture2D>(albedo);
                if(t)
                    Uniform::setTexture2D(programId, "albedo", t->getTextureId());
                else
                    std::cout << "Couldent find texture!" << std::endl;
            }
        }

        TextureUnitManager::popContext();
    }
}