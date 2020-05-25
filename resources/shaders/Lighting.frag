#version 330 core
#define PI 3.1415926538
out vec4 color;

in vec2 uv;

uniform uint renderMode;

uniform sampler2D g_position;    
uniform sampler2D g_normal;
uniform sampler2D g_albedo;      
uniform sampler2D g_metallness_roughness;

uniform samplerCube irradianceMap;     
uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;

uniform vec3 viewPosition;
uniform vec3 lightPosition;
uniform vec3 lightColor;

const vec3 Fdielectric = vec3(0.04);

// Normal distribution function
float distributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return a2 / denom;
}

// Used by method below
float geometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float denom = NdotV * (1.0 - k) + k;

    return NdotV / denom;
}

// Normal distribution function. Describes self-shadowing of microfacets. When a surface is very rough,
// microfacets can overshadow other microfacets which reduces reflected light.
float geometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggxL = geometrySchlickGGX(NdotL, roughness);
    float ggxV = geometrySchlickGGX(NdotV, roughness);

    return ggxL * ggxV;
}

// Describes the ratio of surface reflection at different surface angles.
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

void main()
{
    // Extract position, normal, diffuse, roughness, and metalness from samplers
    vec3 position = texture(g_position, uv).rgb;
    vec3 normal = texture(g_normal, uv).rgb;
    vec3 albedo = pow(texture(g_albedo, uv).rgb, vec3(2.2));
    float metallness = texture(g_metallness_roughness, uv).r;
    float roughness = texture(g_metallness_roughness, uv).g;

    // Calculate direction from fragment to viewPosition
    vec3 V = normalize(viewPosition - position);

    // Reflectance at normal incidence angle
    vec3 F0 = mix(Fdielectric, albedo, metallness);

    // Reflection vector
    vec3 R = reflect(-V, normal);

    // Light contribution
    vec3 Lo = vec3(0.0, 0.0, 0.0);
    //for()
    {
        vec3 L = normalize(lightPosition - position);
        vec3 H = normalize(V + L);
        float distance = length(lightPosition - position);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColor * attenuation;

        // BRDF
        float NDF = distributionGGX(normal, H, roughness);
        float G = geometrySmith(normal, V, L, roughness);
        vec3 F = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

        vec3 nominator = NDF * G * F;
        float denominator = 4 * max(dot(normal, V), 0.0) * max(dot(normal, L), 0.0);
        vec3 specular = nominator / max(denominator, 0.001);

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallness;

        float NdotL = max(dot(normal, L), 0.0);

        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }

    // Calculate ambient lighting from IBL
    vec3 F = fresnelSchlickRoughness(max(dot(normal, V), 0.0), F0, roughness);
    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallness;

    vec3 irradiance = texture(irradianceMap, normal).rgb;
    vec3 diffuse = albedo * irradiance;

    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilterMap, R, roughness * MAX_REFLECTION_LOD).rgb;
    vec2 brdf = texture(brdfLUT, vec2(max(dot(normal, V), 0.0), roughness)).rg;
    vec3 reflection = prefilteredColor * (kS * brdf.x + brdf.y);

    vec3 ambient = (kD * diffuse + reflection * vec3(1.5)); // 1.5 factor to increase reflection contribution for showcase

    vec3 fragmentColor = ambient + Lo;

    if(renderMode == 1u) fragmentColor = albedo;                            // Albedo
    else if(renderMode == 2u) fragmentColor = 0.5 * normal + 0.5;           // Normals
    else if(renderMode == 3u) fragmentColor = vec3(metallness, 0.0, 0.0);   // Metallness
    else if(renderMode == 4u) fragmentColor = vec3(roughness, 0.0, 0.0);    // Roughness
    else if(renderMode == 5u) fragmentColor = kS;                           // Fresnel
    else if(renderMode == 6u) fragmentColor = irradiance;                   // Irradiance
    else if(renderMode == 7u) fragmentColor = reflection;                   // Reflection
    else if(renderMode == 8u) fragmentColor = position;                     // Position

    // HDR tonemapping
    fragmentColor = fragmentColor / (fragmentColor + vec3(1.0));

    // Gamma correction
    fragmentColor = pow(fragmentColor, vec3(1.0/2.2));

    color = vec4(fragmentColor, 1.0);
}