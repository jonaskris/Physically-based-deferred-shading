#version 330 core
out vec4 color;

in vec2 uv;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

void main()
{
    //vec3 position = texture(gPosition, uv).rgb;
    //vec3 normal = texture(gNormal, uv).rgb;
    vec3 albedo = texture(gAlbedo, uv).rgb;

    color = vec4(albedo, 1.0f);
} 