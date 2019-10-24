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
        Window* window;
        std::vector<Renderer*> renderers;

    public:
        RenderManager(Window* window, std::vector<Renderer*> renderers);
        ~RenderManager();

        bool windowClosed() const;

        void render();
    };
}