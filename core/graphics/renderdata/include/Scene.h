#pragma once

#include <vector>

namespace graphics
{
    class Scene
    {
    public:
        unsigned int camera;
        unsigned int skybox;
        std::vector<unsigned int> nodes;

        Scene(unsigned int camera, unsigned int skybox, const std::vector<unsigned int>& nodes) : camera(camera), skybox(skybox), nodes(nodes) {}
    };
}