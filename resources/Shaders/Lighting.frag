#version 330 core
#define PI 3.1415926538
out vec4 color;

in vec2 uv;

uniform sampler2D gPosition;    
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;      
uniform sampler2D gRoughness;
uniform sampler2D gMetalness;
uniform samplerCube skybox;     

uniform vec3 viewPosition;
uniform vec3 lightPosition = vec3(0.0, 1.0, 0.0);
uniform vec3 lightColor = vec3(30.0, 30.0, 30.0);

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
    float rp1 = (roughness + 1.0);
    float k = (rp1*rp1) / 8.0;

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

void main()
{
    // Extract position, normal, albedo, roughness, and metalness from samplers
    vec3 position = texture(gPosition, uv).rgb;
    vec3 normal = texture(gNormal, uv).rgb;
    vec3 albedo = texture(gAlbedo, uv).rgb;
    float roughness = texture(gRoughness, uv).r;
    float metalness = texture(gMetalness, uv).r;

    // Calculate direction from fragment to viewPosition
    vec3 V = normalize(viewPosition - position);

    // Reflectance at normal incidence angle
    vec3 F0 = mix(Fdielectric, albedo, metalness);

    // Calculate radiance from light
    vec3 L = normalize(lightPosition - position);
    vec3 H = normalize(V + L);
    float distance = length(lightPosition - position);
    float attenuation = 1.0 / (distance * distance);
    vec3 radiance = lightColor * attenuation;

    float ND = distributionGGX(normal, H, roughness);
    float G = geometrySmith(normal, V, L, roughness);
    vec3 F = fresnelSchlick(max(dot(H, V), 0.0), F0);

    vec3 nominator = ND * G * F;
    float denominator = 4.0 * max(dot(V, normal), 0.0) * max(dot(L, normal), 0.0) + 0.001f;
    vec3 brdf = nominator / denominator;

    vec3 Ks = F;

    vec3 Kd = vec3(1.0) - Ks;
    Kd *= 1.0 - metalness;

    float NdotL = max(dot(normal, L), 0.0);

    radiance = (Kd * albedo / PI + brdf) * radiance * NdotL;
   

    // Calculate final color 
    vec3 ambient = albedo * vec3(0.2); // Ambient light contribution to avoid completely black shadows

    vec3 c = ambient + radiance;

    c = c / (c + vec3(1.0));

    color = vec4(c, 1.0);
} 