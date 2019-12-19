#version 330 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
  
//out vec4 color;
out vec3 fragNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vec4 worldPos = vec4(in_position, 1.0);

    //color = vec4(0.7, 0.0, 1.0, 1.0);
    fragNormal = in_normal;

    gl_Position =  projection * view * model * worldPos; // Model * View * Projection
}