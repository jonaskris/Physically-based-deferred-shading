#version 330 core
out vec4 out_color;
  
//in vec4 color;
in vec3 fragNormal;

uniform samplerCube albedo;

void main()
{
    //out_color = vertexColor;
    out_color = vec4(texture(albedo, fragNormal).rgb, 1.0);
    //out_color = vec4( fragNormal * vec3(1.0, 1.0, 1.0), 1.0);
} 