#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vec2.h>
#include <Vec3.h>

#define VERTEX_ATTRIBUTE_POSITION 0 
#define VERTEX_ATTRIBUTE_NORMAL 1
#define VERTEX_ATTRIBUTE_UV 2

struct CubemappedVertex
{
    math::vec3 position;
    math::vec3 normal;

    CubemappedVertex(const math::vec3& position) : position(position), normal(position.normalize()) {};
    CubemappedVertex(const math::vec3& position, const math::vec3& normal) : position(position), normal(normal) {};

    static void describeVAOLayout()
    {
        glEnableVertexAttribArray(VERTEX_ATTRIBUTE_POSITION);
        glVertexAttribPointer(VERTEX_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(CubemappedVertex), (const GLvoid*)(offsetof(CubemappedVertex, CubemappedVertex::position)));
        glEnableVertexAttribArray(VERTEX_ATTRIBUTE_NORMAL);
        glVertexAttribPointer(VERTEX_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(CubemappedVertex), (const GLvoid*)(offsetof(CubemappedVertex, CubemappedVertex::normal)));    
    }
};

struct TexturemappedVertex
{
    math::vec3 position;
    math::vec3 normal;
    math::vec2 uv;

    TexturemappedVertex(const math::vec3& position, const math::vec2& uv) : position(position), normal(position.normalize()), uv(uv) {};
    TexturemappedVertex(const math::vec3& position, const math::vec3& normal, const math::vec2& uv) : position(position), normal(normal), uv(uv) {};

    static void describeVAOLayout()
    {
        glEnableVertexAttribArray(VERTEX_ATTRIBUTE_POSITION);
        glVertexAttribPointer(VERTEX_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(TexturemappedVertex), (const GLvoid*)(offsetof(TexturemappedVertex, TexturemappedVertex::position)));
        glEnableVertexAttribArray(VERTEX_ATTRIBUTE_NORMAL);
        glVertexAttribPointer(VERTEX_ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_TRUE, sizeof(TexturemappedVertex), (const GLvoid*)(offsetof(TexturemappedVertex, TexturemappedVertex::normal)));            
    
        glEnableVertexAttribArray(VERTEX_ATTRIBUTE_UV);
        glVertexAttribPointer(VERTEX_ATTRIBUTE_UV, 2, GL_FLOAT, GL_TRUE, sizeof(TexturemappedVertex), (const GLvoid*)(offsetof(TexturemappedVertex, TexturemappedVertex::uv)));            
    }
};

struct SimpleTexturemappedVertex
{
    math::vec3 position;
    math::vec2 uv;

    SimpleTexturemappedVertex(const math::vec3& position, const math::vec2& uv) : position(position), uv(uv) {};

    static void describeVAOLayout()
    {
        glEnableVertexAttribArray(VERTEX_ATTRIBUTE_POSITION);
        glVertexAttribPointer(VERTEX_ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleTexturemappedVertex), (const GLvoid*)(offsetof(SimpleTexturemappedVertex, SimpleTexturemappedVertex::position)));
    
        glEnableVertexAttribArray(VERTEX_ATTRIBUTE_UV);
        glVertexAttribPointer(VERTEX_ATTRIBUTE_UV, 2, GL_FLOAT, GL_TRUE, sizeof(SimpleTexturemappedVertex), (const GLvoid*)(offsetof(SimpleTexturemappedVertex, SimpleTexturemappedVertex::uv)));            
    
    }
};