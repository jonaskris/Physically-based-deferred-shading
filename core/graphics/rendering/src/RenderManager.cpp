#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <RenderManager.h>
#include <Renderer.h>
#include <Window.h>

namespace graphics
{
    RenderManager::RenderManager(size_t width, size_t height, const std::vector<Renderer*>& renderers) : renderers(renderers) 
    {
        window = new Window(width, height, "");
        
        // Initialize OpenGL
        if(!gladLoadGL())
            std::cerr << "Failed to initialize GLAD!" << std::endl;
        else
            std::cout << "GLAD initialized!\n\tVersion: " << GLVersion.major << "." << GLVersion.minor << std::endl;

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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Execute every renderer
            for(Renderer* renderer : renderers)
                renderer->render();

        // Update window
            // Check for OpenGL errors
            GLenum error = glGetError();
            if(error != GL_NO_ERROR)
                std::cout << "OpenGL error: " << error << std::endl;

            // Poll events, swap buffers
            window->update();
    }
}