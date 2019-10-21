#include <vector>
#include <glad/glad.h>
#include <RenderManager.h>
#include <Renderer.h>
#include <Window.h>

namespace graphics
{
    RenderManager::RenderManager(size_t width, size_t height, const std::vector<Renderer*>& renderers) : renderers(renderers) 
    {
        window = new Window(width, height, "");

        glEnable(GL_DEPTH_TEST);
        glFrontFace(GL_CW);
        glDisable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glClearColor(1.0f, 0.7f, 0.3f, 1.0f);
    };

    RenderManager::~RenderManager()
    {
        delete window;
        for(Renderer* renderer : renderers)
            delete renderer;
    };

    bool RenderManager::windowClosed() const { return window->closed(); }

    void RenderManager::render()
    {
        // Clear window
        window->clear();

        // Render every renderer
        for(Renderer* renderer : renderers)
            renderer->render();

        // Update window
        window->update();
    }
}