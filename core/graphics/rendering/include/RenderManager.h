#pragma once

#include <vector>

namespace graphics
{
    class Renderer;
    class Window;
    
    /*
        The RenderManager controls the window, executes renderers in the order given, and performs
        once-per-frame actions such as clearing the window before rendering,
        and updating the window after rendering.
    */
    class RenderManager
    {
    private:
        std::vector<Renderer*> renderers;
        Window* window = nullptr;

    public:
        RenderManager(size_t width, size_t height, const std::vector<Renderer*>& renderers);
        ~RenderManager();

        bool windowClosed() const;

        void render();
    };
}