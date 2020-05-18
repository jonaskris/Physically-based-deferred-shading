#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;

out vec3 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    uv = in_position;

    vec4 worldPosition = projection * view * model * vec4(in_position, 1.0);
    gl_Position = worldPosition.xyww;
}