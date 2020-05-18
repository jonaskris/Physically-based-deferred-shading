#pragma once

#include <vector>

#include <RenderQueue.h>
#include <Node.h>
#include <Mesh.h>
#include <Camera.h>
#include <Skybox.h>

namespace graphics
{
    struct Scene
    {
        std::vector<Node> nodes; // Top level nodes

        Camera* camera;
        Skybox skybox;

    // Render queue
        RenderQueue renderQueue;

        Scene(Camera* camera, const Skybox& skybox, const std::vector<Node>& nodes) : camera(camera), skybox(skybox), nodes(nodes) {}

        void addNode(const Node& node)
        {
            nodes.push_back(node);
        }
    };
}