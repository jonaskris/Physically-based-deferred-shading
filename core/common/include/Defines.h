#pragma once

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
    
    enum class NumeralType
    {
        FLOAT = 1, VEC2 = 2, VEC3 = 3, VEC4 = 4
    };

    enum class SamplerType
    {
        SAMPLERCUBE, SAMPLER2D
    };

    enum class ShaderType
    {
        VERTEX, FRAGMENT, GEOMETRY, TESS_EVALUATION, TESS_CONTROL, COMPUTE
    };

    enum class ProgramType
    {
        GEOMETRY, LIGHTING, SKYBOX, IRRADIANCEMAP, PREFILTERMAP, BRDFLUT
    };
}