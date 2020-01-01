#pragma once

#include <glad/glad.h>

#include <Node.h>

namespace graphics
{
    class Model : public Node
    {
    private:
        unsigned int mesh = 0, material = 0;

    public:
        Model(unsigned int mesh, unsigned int material);

        void process(GLuint programId) override;
    };
}