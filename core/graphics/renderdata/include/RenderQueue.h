#pragma once

#include <cstdint>
#include <vector>
#include <algorithm>

#include <Node.h>
#include <Transform.h>
#include <DataIdentifier.h>
#include <Shader.h>
#include <DrawKey.h>
#include <DrawUnit.h>

#include <Mat4.h>

namespace graphics
{
    class RenderQueue
    {
    private:
        std::vector<math::Mat4> transforms;
        std::vector<uint64_t> drawKeys;

        void processNode(Node& node, uint32_t parentTransform = 0)
        {
            math::Mat4 transform;
            if(parentTransform)
                transform = transforms[parentTransform - 1] * node.transform.toMatrix();
            else
                transform = node.transform.toMatrix();

            transforms.push_back(transform);

            size_t transformSize = transforms.size();
            
            for(DrawUnit drawUnit : node.drawUnits)
                drawKeys.push_back(DrawKey::write(drawUnit.program.identifier, drawUnit.material.identifier, drawUnit.mesh.identifier, transformSize - 1));

            for(Node& node : node.children)
                processNode(node, transformSize);
        }

    public:
        RenderQueue() {}

        void process(std::vector<Node>& sceneNodes)
        {
            for(Node& node : sceneNodes)
                processNode(node);

            std::sort(drawKeys.begin(), drawKeys.end()); // TODO: Sort only added drawkeys per scene and merge two sorted halves with inplace_merge
        }

        void reset()
        {
            transforms.clear();
            drawKeys.clear();
        }

        const std::vector<uint64_t>& getDrawKeys() const { return drawKeys; }
        const std::vector<math::Mat4>& getTransforms() const { return transforms; }
    };
}