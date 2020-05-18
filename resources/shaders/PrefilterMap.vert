#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

out vec3 normal;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    normal = in_normal;
    gl_Position = projection * view * vec4(in_position, 1.0);
}