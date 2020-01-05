#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
  
out vec3 position;
out vec3 normal;
out vec3 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    normal = in_normal;
    uv = in_position;

    vec4 worldPosition = projection * view * model * vec4(in_position, 1.0);
    position = vec3(worldPosition);
    gl_Position = worldPosition;
}