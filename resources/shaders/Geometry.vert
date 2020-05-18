#version 400 core
layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec3 in_tangent;
layout (location = 3) in vec3 in_bitangent;
layout (location = 4) in vec2 in_uv;

out vec3 position;
out vec3 normal;
out vec3 tangent;
out vec3 bitangent;
out vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vec4 worldPosition = model * vec4(in_position, 1.0);
    position = worldPosition.xyz;

    mat3 normalMatrix = transpose(inverse(mat3(model)));
    normal = normalize(normalMatrix * in_normal);
    tangent = normalize(normalMatrix * in_tangent);
    bitangent = normalize(normalMatrix * in_bitangent);

    uv = in_uv;
    gl_Position = projection * view * worldPosition;
}