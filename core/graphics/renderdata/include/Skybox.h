#pragma once

#include <glad/glad.h>

#include <Model.h>
#include <Transform.h>

namespace graphics
{
    class Skybox : public Model
    {
    public:
        Skybox(unsigned int mesh, unsigned int material);

        void process(GLuint programId, math::Mat4 parentTransform = {}) override;
    };
}