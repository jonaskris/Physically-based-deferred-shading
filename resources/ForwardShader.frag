#version 330 core
out vec4 out_color;
  
in vec4 vertexColor;

void main()
{
    out_color = vertexColor;
} 