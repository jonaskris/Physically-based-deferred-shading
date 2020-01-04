#pragma once

#include <glad/glad.h>

#include <Node.h>
#include <Transform.h>

namespace graphics
{
    class Model : public Node
    {
    private:
        unsigned int mesh = 0, material = 0;

    public:
        Model(unsigned int mesh, unsigned int material, math::Transform transform, std::vector<unsigned int> childrenNodes);

        void process(GLuint programId, math::Mat4 parentTransform = {}) override;
    };
}