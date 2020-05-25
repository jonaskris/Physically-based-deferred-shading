#include <Material.h>

#include <DataStore.h>
#include <TextureUnitManager.h>

namespace graphics
{
    void Material::setMaterialAttribute(Program& program, const MaterialAttribute& materialAttribute, const std::string& name, size_t index) const
    {
        if(materialAttribute.texture.identifier)
        {
            program.setTexture2D("samplers[" + std::to_string(index) + "]", DataStore::get<Texture>(materialAttribute.texture)->getTextureId());
            program.setUniform1ui(name + ".samplerIndex", index);        
            program.setUniform1b(name + ".usesSampler", true);
        } else
        {
            program.setUniformVec4f(name + ".color", materialAttribute.color);
            program.setUniform1b(name + ".usesSampler", false);
        }
    }

    Material::Material(const Material::MaterialAttribute& materialAttributeAlbedo, const Material::MaterialAttribute& materialAttributeNormal, const Material::MaterialAttribute& materialAttributeMetallnessRoughness, bool doubleSided) 
    : materialAttributeAlbedo(materialAttributeAlbedo), materialAttributeNormal(materialAttributeNormal), materialAttributeMetallnessRoughness(materialAttributeMetallnessRoughness), doubleSided(doubleSided) {}

    void Material::set(Program& program, bool& doubleSided)
    {
        doubleSided = this->doubleSided;
        TextureUnitManager::pushContext();

        setMaterialAttribute(program, materialAttributeAlbedo, "materialAttributeAlbedo", 0);
        setMaterialAttribute(program, materialAttributeNormal, "materialAttributeNormal", 1);
        setMaterialAttribute(program, materialAttributeMetallnessRoughness, "materialAttributeMetallnessRoughness", 2);

        TextureUnitManager::popContext();
    }
}