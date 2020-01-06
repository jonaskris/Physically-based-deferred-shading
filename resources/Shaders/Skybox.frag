#version 330 core
out vec4 color;

in vec3 uv;

uniform samplerCube albedo;

void main()
{
    color = texture(albedo, uv);
} 