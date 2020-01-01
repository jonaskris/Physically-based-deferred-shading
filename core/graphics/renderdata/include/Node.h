#pragma once

#include <glad/glad.h>

#include <vector>
#include <string>

namespace graphics
{
    class Node
    {
    private:
        std::vector<unsigned int> childrenNodes;

    protected:
        Node(const std::vector<unsigned int>& childrenNodes = {})
        : childrenNodes(childrenNodes) {}

    public:
        virtual void process(GLuint programId) = 0;
    };
}