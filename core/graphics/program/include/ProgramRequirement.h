#pragma once

#include <cstddef>
#include <vector>
#include <utility>
#include <string>

#include <Defines.h>
#include <ProgramRequirement.h>

namespace graphics
{
    struct ProgramRequirement
    {   
        /*struct SamplerUsageRequirement
        {
            size_t uvChannel;
            size_t samplerRequirement; // Index of vector
            size_t shift; // Nr of components to shift before sampling MaterialAttributeRequirement::type nr of components

            friend bool operator==(const SamplerUsageRequirement& lhs, const SamplerUsageRequirement& rhs)
            {
                return lhs.uvChannel == rhs.uvChannel && lhs.samplerRequirement == rhs.samplerRequirement && lhs.shift == rhs.shift;
            }
        };

        struct SamplerRequirement
        {
            defines::SamplerType samplerType;
        };

        std::vector<SamplerRequirement> samplerRequirements;

        struct MaterialAttributeRequirement
        {
            defines::MaterialAttribute materialAttribute;
            defines::NumeralType type;

            SamplerUsageRequirement samplerUsageRequirement;

            MaterialAttributeRequirement(defines::MaterialAttribute materialAttribute, defines::NumeralType type) : materialAttribute(materialAttribute), type(type) {}

            friend bool operator==(const MaterialAttributeRequirement& lhs, const MaterialAttributeRequirement& rhs)
            {
                return lhs.materialAttribute == rhs.materialAttribute && lhs.type == rhs.type && lhs.samplerUsageRequirement == rhs.samplerUsageRequirement;
            }
        };

        std::vector<MaterialAttributeRequirement> materialAttributeRequirements;

        // Mesh requirements
        struct VertexAttributeRequirement
        {
            defines::VertexAttribute vertexAttribute;
            defines::NumeralType type;
            size_t index;

            friend bool operator==(const VertexAttributeRequirement& lhs, const VertexAttributeRequirement& rhs)
            {
                return lhs.vertexAttribute == rhs.vertexAttribute && lhs.type == rhs.type && lhs.index == rhs.index;
            }
        };

        std::vector<VertexAttributeRequirement> vertexAttributeRequirements;*/

        static ProgramRequirement merge(const ProgramRequirement& meshRequirement, const ProgramRequirement& materialRequirement)
        {
            ProgramRequirement returnProgramRequirement;
            returnProgramRequirement.hasTangentSpace = meshRequirement.hasTangentSpace;
            returnProgramRequirement.hasUV = meshRequirement.hasUV;
            returnProgramRequirement.normalMapped = materialRequirement.normalMapped;
            return returnProgramRequirement;
        }
        bool hasTangentSpace;   // Has tangents and bitangents, required if normalMapped
        bool hasUV;             // Vertices has UV's, if not, normals are used as uv
        bool normalMapped;      // Uses a normal texture

        friend bool operator==(const ProgramRequirement& lhs, const ProgramRequirement& rhs)
        {
            return lhs.normalMapped == rhs.normalMapped && lhs.hasTangentSpace == rhs.hasTangentSpace && lhs.hasUV == rhs.hasUV;
        }    
    };
}