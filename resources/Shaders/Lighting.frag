#version 330 core
out vec4 color;

in vec2 uv;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gRoughness;
uniform sampler2D gMetalness;
uniform samplerCube skybox;

uniform vec3 viewPosition;

void main()
{
    // Extract position, normal, albedo, metalness and roughness from samplers

    vec3 position = texture(gPosition, uv).rgb;
    vec3 normal = texture(gNormal, uv).rgb;
    vec3 diffuse = texture(gAlbedo, uv).rgb;
    vec3 roughness = texture(gRoughness, uv).rrr;
    vec3 metalness = texture(gMetalness, uv).rrr;

    vec3 reflectionAngle = reflect(position - viewPosition, normal);
    vec3 reflectionDiffuse = texture(skybox, reflectionAngle).rgb;

    color = vec4(diffuse + reflectionDiffuse * 0.2, 1.0);
} 