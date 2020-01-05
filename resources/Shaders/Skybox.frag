#version 330 core
out vec4 color;

in vec3 uv;

uniform samplerCube albedo;

void main()
{
    color = vec4(texture(albedo, uv).rgb, 1.0);
} 