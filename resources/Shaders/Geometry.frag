#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gAlbedo;
layout (location = 3) out float gRoughness;
layout (location = 4) out float gMetalness;

in vec3 position;
in vec3 normal;
in vec3 uv;

uniform samplerCube albedo;
uniform samplerCube roughness;
uniform samplerCube metalness;

void main()
{
    gPosition = position;
    gNormal = normal;
    
    gAlbedo = texture(albedo, uv).rgb;
    gRoughness = texture(roughness, uv).r;
    gMetalness = texture(metalness, uv).r;
} 