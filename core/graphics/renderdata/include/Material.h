#pragma once

#include <DataIdentifier.h>
#include <Texture.h>
#include <Vec4.h>
#include <Program.h>

namespace graphics
{
    struct Material
    {
    public:
        struct MaterialAttribute
        {
            DataIdentifier<Texture> texture;
            math::Vec4 color; // If no texture, color is used
            size_t components;
        };  

    private:
        MaterialAttribute materialAttributeAlbedo;
        MaterialAttribute materialAttributeNormal;
        MaterialAttribute materialAttributeMetallnessRoughness;

        bool doubleSided;

        void setMaterialAttribute(Program& program, const MaterialAttribute& materialAttribute, const std::string& name, size_t index) const;

    public:
        Material(const Material::MaterialAttribute& materialAttributeAlbedo, const Material::MaterialAttribute& materialAttributeNormal, const Material::MaterialAttribute& materialAttributeMetallnessRoughness, bool doubleSided);

        void set(Program& program, bool& doubleSided);
    };
}