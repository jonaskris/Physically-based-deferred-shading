#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>

#include <Mat4.h>
#include <Transform.h>

namespace graphics
{
    class Node
    {
    protected:
        std::vector<unsigned int> childrenNodes;

        math::Transform transform;

        Node(std::vector<unsigned int> childrenNodes = {}, math::Transform transform = {})
        : transform(transform), childrenNodes(childrenNodes) {}

        Node(math::Transform transform = {}, std::vector<unsigned int> childrenNodes = {})
        : transform(transform), childrenNodes(childrenNodes) {}

    public:
        virtual void process(GLuint programId, math::Mat4 parentTransform = {}) = 0;
    };
}