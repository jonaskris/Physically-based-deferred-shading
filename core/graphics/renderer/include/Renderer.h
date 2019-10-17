#include <glad/glad.h>
#include <Window.h>
#include <Framebuffer.h>


namespace graphics
{
    class Renderer
    {
    private:
        Window* window = nullptr;
        Framebuffer* framebuffer = nullptr;

    public:
        Renderer(size_t width, size_t height)
        {   
            window = new Window(width, height, "");
            
            framebuffer = new Framebuffer(width, height);

            glEnable(GL_DEPTH_TEST);

            glFrontFace(GL_CW);
            glDisable(GL_CULL_FACE);
            glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
            glClearColor(1.0f, 0.7f, 0.3f, 1.0f);
        };

        ~Renderer() { delete framebuffer; delete window; };

        bool windowClosed() { return window->closed();}

        void render()
        {
            window->clear();
            framebuffer->bind();

            // enable geometry shader

            // set uniforms

            // draw
            
            framebuffer->unbind();
            window->clear();

            // enable lighting shader

            // set uniforms

            // bind framebuffer textures

            // draw quad

            window->update();
        }

    };
}