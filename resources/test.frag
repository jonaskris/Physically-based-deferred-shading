#version 330 core
out vec4 out_color;
  
in vec4 FragmentColor;

void main()
{
    out_color = FragmentColor;
} 