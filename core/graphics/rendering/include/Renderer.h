#pragma once

namespace graphics
{
    class Renderer
    {
    public:
        virtual ~Renderer() {};

        virtual void render() = 0;
    };
}