#include <GeometryProgramGenerator.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <ProgramRequirement.h>

namespace graphics
{
    DataIdentifier<Program> GeometryProgramGenerator::generate(const ProgramRequirement& programRequirement)
    {
    // Vertex shader
        std::string vertexShaderCode;

        // Vertex input
        vertexShaderCode.append(
            "#version 330 core\n"
            "layout (location = 0) in vec3 in_position;\n"
            "layout (location = 1) in vec3 in_normal;\n"
            "layout (location = 2) in vec3 in_tangent;\n"
            "layout (location = 3) in vec3 in_bitangent;\n"
            "layout (location = 4) in vec2 in_uv;\n"
        );

        // Vertex output
        vertexShaderCode.append(
            "\n"
            "out vec3 position;\n"
            "out vec3 normal;\n"
            "out vec2 uv;\n"
        );

        if(programRequirement.normalMapped && programRequirement.hasTangentSpace)
            vertexShaderCode.append
            (
                "out vec3 tangent;\n"
                "out vec3 bitangent;\n"
            );

        vertexShaderCode.append("\n");

        // Uniforms
        vertexShaderCode.append
        (
            "uniform mat4 projection;\n"
            "uniform mat4 view;\n"
            "uniform mat4 model;\n"
        );
        vertexShaderCode.append("\n");


        // Vertex main
        vertexShaderCode.append
        (
            "void main()\n"
            "{\n"
            "\tvec4 worldPosition = model * vec4(in_position, 1.0);\n"
            "\tposition = worldPosition.xyz;\n"
            "\tgl_Position = projection * view * worldPosition;\n\n"
            "\tmat3 normalMatrix = transpose(inverse(mat3(model)));\n"
            "\tnormal = normalize(normalMatrix * in_normal);\n"
            "\tuv = in_uv;\n"
        );

        if(programRequirement.hasTangentSpace && programRequirement.normalMapped)
            vertexShaderCode.append
            (
                "\ttangent = normalize(normalMatrix * in_tangent);\n"
                "\tbitangent = normalize(normalMatrix * in_bitangent);\n"
            );

        vertexShaderCode.append("}");

    // Fragment shader
        std::string fragmentShaderCode;

        // Fragment out
        fragmentShaderCode.append(
            "#version 330 core\n"
            "layout (location = 0) out vec3 g_position;\n"
            "layout (location = 1) out vec3 g_normal;\n"
            "layout (location = 2) out vec3 g_albedo;\n"
            "layout (location = 3) out vec2 g_metallness_roughness;\n\n"
        );       

        // Fragment structs
        fragmentShaderCode.append
        (
            "struct MaterialAttribute\n"
            "{\n"
            "\tbool usesSampler;\n"
            "\tvec4 color;\n"
            "\tuniform sampler2D texture;\n"
            "};\n\n"
        );

        // Fragment helper methods
        fragmentShaderCode.append
        (
            "vec4 evaluateMaterialAttribute(MaterialAttribute materialAttribute, vec2 uv)\n"
            "{\n"
            "\tif(materialAttribute.usesSampler)\n"
            "\t\treturn texture(materialAttribute.texture, uv).rgba;\n"
            "\telse\n"
            "\t\treturn materialAttribute.color;\n"
            "};\n\n"
        );

        // Fragment in
        fragmentShaderCode.append(
            "in vec3 position;\n"
            "in vec3 normal;\n"
            "in vec2 uv;\n"
        );

        if(programRequirement.normalMapped && programRequirement.hasTangentSpace)
            fragmentShaderCode.append
            (
                "in vec3 tangent;\n"
                "in vec3 bitangent;\n"
            );   

        fragmentShaderCode.append("\n");

        // Fragment uniforms
        size_t samplerCount = programRequirement.normalMapped ? 3 : 2;
        for(size_t i = 0; i < samplerCount; i++)
            fragmentShaderCode.append
            (
                "uniform MaterialAttribute materialAttribute_" + std::to_string(i) + ";\n"
            );


        fragmentShaderCode.append("\n");

        // Fragment main
        fragmentShaderCode.append
        (
            "void main()\n"
            "{\n"
            "\tg_position = position;\n\n"
        );

        if(programRequirement.hasTangentSpace && programRequirement.normalMapped)
            fragmentShaderCode.append
            (
                "\tvec3 T = normalize(tangent);\n"
                "\tvec3 N = normalize(normal);\n"
                "\tT = normalize(T - dot(T, N) * N);\n"
                "\tvec3 B = normalize(bitangent);\n"
                "\tmat3 TBN = mat3(T, B, N);\n"
                "\tvec3 sampledNormal = 2.0 * evaluateMaterialAttribute(materialAttribute_1, uv).rgb - vec3(1.0);\n"
                "\tg_normal = normalize(TBN * sampledNormal);\n\n"
            );

        fragmentShaderCode.append
        (
            "\tg_albedo = evaluateMaterialAttribute(materialAttribute_0, uv).rgb;\n"
            "\tg_metallness_roughness = evaluateMaterialAttribute(materialAttribute_2, uv).rg;\n"
            "}"
        );

        std::cout << "vertexShaderCode: \n" << vertexShaderCode << std::endl;
        std::cout << "fragmentShaderCode: \n" << fragmentShaderCode << std::endl;
        std::cin.get();

        return DataStore::insert<Program>(new Program({{vertexShaderCode, ShaderType::VERTEX}, {fragmentShaderCode, ShaderType::FRAGMENT}}));
    }
}