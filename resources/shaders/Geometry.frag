#version 400 core
layout (location = 0) out vec3 g_position;
layout (location = 1) out vec3 g_normal;
layout (location = 2) out vec3 g_albedo;
layout (location = 3) out vec2 g_metallness_roughness;

struct MaterialAttribute
{
    bool usesSampler;
    vec4 color;
    uint samplerIndex;
};

in vec3 position;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;
in vec2 uv;

uniform sampler2D samplers[3];

uniform MaterialAttribute materialAttributeAlbedo;
uniform MaterialAttribute materialAttributeNormal;
uniform MaterialAttribute materialAttributeMetallnessRoughness;
        
vec4 evaluateMaterialAttribute(MaterialAttribute materialAttribute, vec2 uv)
{
    if(materialAttribute.usesSampler)
        return texture(samplers[materialAttribute.samplerIndex], uv).rgba;
    else
        return materialAttribute.color;
};

void main()
{
    g_position = position;
    g_albedo = evaluateMaterialAttribute(materialAttributeAlbedo, uv).rgb;

    if(materialAttributeNormal.usesSampler)
    {
        vec3 T = normalize(tangent);
        vec3 N = normalize(normal);
        T = normalize(T - dot(T, N) * N);
        vec3 B = normalize(bitangent);
        mat3 TBN = mat3(T, B, N);

        vec3 sampledNormal = 2.0 * evaluateMaterialAttribute(materialAttributeNormal, uv).rgb - vec3(1.0);
        g_normal = normalize(TBN * sampledNormal);
    } else
    {
        g_normal = normal;
    }

    g_metallness_roughness = evaluateMaterialAttribute(materialAttributeMetallnessRoughness, uv).rg;
}