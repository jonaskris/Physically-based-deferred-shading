#version 330 core
out vec4 color;

in vec3 uv;

uniform samplerCube skybox;

void main()
{
    color = vec4(texture(skybox, uv, 1.2).rgb, 1.0);
} 