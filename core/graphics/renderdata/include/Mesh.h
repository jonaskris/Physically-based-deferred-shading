#pragma once

#include <set>

#include <glad/glad.h>

#include <Geometry.h>
#include <VertexAttribute.h>
//#include <ProgramRequirement.h>

namespace graphics
{
    class Mesh
    {
    private:
        GLuint VAO, VBO, EBO;
        GLuint indicesCount;
        GLenum drawMode;

        //ProgramRequirement programRequirement; // Used to figure out the appropriate shader

    public:
        Mesh(const math::geometry::Geometry& geometry)
        : indicesCount(geometry.getIndices().size()), drawMode(geometry.getDrawMode())
        {            
            // VBO
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, geometry.getVertices().size() * sizeof(float), &geometry.getVertices()[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // EBO
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry.getIndices().size() * sizeof(uint32_t), &geometry.getIndices()[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            // VAO
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


            //bool hasTangents, hasBitangents, hasUV;
            // Vertex attributes
            for(size_t i = 0; i < geometry.getVertexAttributes().size(); i++)
            {
                const math::geometry::VertexAttribute& vertexAttribute = geometry.getVertexAttributes()[i];
                glEnableVertexAttribArray(i);
                glVertexAttribPointer(i, (GLint)vertexAttribute.numeralType, vertexAttribute.type, vertexAttribute.normalized, vertexAttribute.stride, vertexAttribute.offset);            
            
                /*if(vertexAttribute.vertexAttribute == defines::VertexAttribute::TANGENT)
                    hasTangents = true;
                else if(vertexAttribute.vertexAttribute == defines::VertexAttribute::BITANGENT)
                    hasBitangents = true;
                else if(vertexAttribute.vertexAttribute == defines::VertexAttribute::UV)
                    hasUV = true;    */        
            }

            /*if(hasTangents && hasBitangents)
                programRequirement.hasTangentSpace = true;
            if(hasUV)
                programRequirement.hasUV = true;*/

            glBindVertexArray(0);
        }

        void draw()
        {
            glBindVertexArray(VAO);
            glDrawElements(drawMode, indicesCount, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        //const ProgramRequirement& getProgramRequirement() const { return programRequirement; }
    };
}