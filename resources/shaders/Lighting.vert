#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_uv;
  
out vec2 uv;

uniform mat4 projection;

void main()
{
    uv = in_uv;
    gl_Position = projection * vec4(in_position, 1.0);
}