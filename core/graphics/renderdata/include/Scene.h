#pragma once

#include <vector>

namespace graphics
{
    class Scene
    {
    public:
        unsigned int camera;
        std::vector<unsigned int> nodes;

        Scene(unsigned int camera, const std::vector<unsigned int>& nodes) : camera(camera), nodes(nodes) {}
    };
}