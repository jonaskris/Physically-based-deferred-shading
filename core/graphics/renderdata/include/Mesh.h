#pragma once

#include <string>
#include <vector>
#include <utility>
#include <optional>

#include <GL/gl.h>

#include <DataIdentifier.h>

namespace graphics
{
    class Mesh
    {
    private:
        GLuint VAO, VBO, EBO;
        std::vector<Texture> textures;

    public:
        Mesh(float* positions, float* normals, float* textureCoordinates, unsigned int* indices, size_t verticesCount, size_t indicesCount) 
        {
            // Calculate vertex size
            size_t floatsPerVertex = 0;

            floatsPerVertex += 3; // Position
            floatsPerVertex += 3; // Normal
            if(textureCoordinates) floatsPerVertex += 2; // Texture coordinate

            // Create vertex vector
            std::vector<float> vertices(verticesCount * floatsPerVertex);
            for(size_t i = 0; i < verticesCount; i++)
            {
                // Position
                vertices.push_back(positions[i * 3]);
                vertices.push_back(positions[i * 3 + 1]);
                vertices.push_back(positions[i * 3 + 2]);

                // Normal
                vertices.push_back(normals[i * 3]);
                vertices.push_back(normals[i * 3 + 1]);
                vertices.push_back(normals[i * 3 + 2]);

                // Texture coordinate
                if(textureCoordinates)
                {
                    vertices.push_back(normals[i * 2]);
                    vertices.push_back(normals[i * 2 + 1]);
                }
            }

            // Convert indices to 32 bit unsigned int
            std::vector<uint32_t> indicesConverted(indicesCount);
            for(size_t i = 0; i < indicesCount; i++)
                indicesConverted.push_back((uint32_t)indices[i]);


            // VBO
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, verticesCount * floatsPerVertex * sizeof(float), &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // EBO
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * indicesCount, &indicesConverted[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            // VAO
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            // Vertex attributes
            // Position
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(va.index, va.size, va.type, va.normalized, va.stride, va.offset);

            glBindVertexArray(0);
        }



        void drawMesh()
        {
            // Bind textures

            // Draw VAO
        }
    };
}