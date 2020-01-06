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
    vec4 worldPosition = model * vec4(in_position, 1.0);
    position = worldPosition.xyz;

    uv = in_position;
    normal = normalize(transpose(inverse(mat3(model))) * in_normal);

    gl_Position = projection * view * worldPosition;
}