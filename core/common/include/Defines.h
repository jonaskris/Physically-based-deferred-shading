#pragma once

#include <string>

namespace defines
{

    enum class MaterialAttribute
    {
        ALBEDO, NORMAL, METALLNESS_ROUGHNESS
    };

    enum class VertexAttribute
    {
        POSITION, NORMAL, TANGENT, BITANGENT, UV, COLOR
    };
    
    enum class Operation
    {
        ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION
    };
    
    enum class NumeralType
    {
        FLOAT = 1, VEC2 = 2, VEC3 = 3, VEC4 = 4
    };

    enum class SamplerType
    {
        SAMPLERCUBE, SAMPLER2D
    };

    inline std::string toString(MaterialAttribute materialAttribute)
    {
        switch(materialAttribute)
        {
            case MaterialAttribute::ALBEDO: return "albedo";
            case MaterialAttribute::NORMAL: return "normal";
            case MaterialAttribute::METALLNESS_ROUGHNESS: return "metallness_roughness";
            default: return "Failed to convert MaterialAttribute enum to string!";
        }
    }

    inline std::string toString(VertexAttribute vertexAttribute)
    {
        switch(vertexAttribute)
        {
            case VertexAttribute::POSITION: return "position";
            case VertexAttribute::NORMAL: return "normal";
            case VertexAttribute::TANGENT: return "tangent";
            case VertexAttribute::BITANGENT: return "bitangent";
            case VertexAttribute::UV: return "uv";
            case VertexAttribute::COLOR: return "color";
            default: return "Failed to convert VertexAttribute enum to string!";
        }
    }

    inline std::string toString(Operation operation)
    {
        switch(operation)
        {
            case Operation::ADDITION: return "+";
            case Operation::DIVISION: return "/";
            case Operation::MULTIPLICATION: return "*";
            case Operation::SUBTRACTION: return "-";
            default: return "Failed to convert Operation enum to string!";
        }
    }

    inline std::string toString(NumeralType numeralType)
    {
        switch(numeralType)
        {
            case NumeralType::FLOAT: return "float";
            case NumeralType::VEC2: return "vec2";
            case NumeralType::VEC3: return "vec3";
            case NumeralType::VEC4: return "vec4";
            default: return "Failed to convert NumeralType enum to string!";
        }
    }

    inline std::string toString(SamplerType samplerType)
    {
        switch(samplerType)
        {
            case SamplerType::SAMPLER2D: return "sampler2D";
            case SamplerType::SAMPLERCUBE: return "samplerCube";
            default: return "Failed to convert SamplerType enum to string!";
        }
    }
}