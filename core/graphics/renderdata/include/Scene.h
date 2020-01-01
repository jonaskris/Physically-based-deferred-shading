#pragma once

#include <vector>

namespace graphics
{
    class Scene
    {
    public:
        std::vector<unsigned int> nodes;

        Scene(const std::vector<unsigned int>& nodes) : nodes(nodes) {}
    };
}