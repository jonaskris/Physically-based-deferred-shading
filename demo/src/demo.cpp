#include <iostream>
#include <vector>
#include <Icosphere.h>
#include <Program.h>
#include <Shader.h>
#include <RenderManager.h>
#include <Scene.h>
#include <Camera.h>
#include <Vec3.h>
#include <Sampler.h>
#include <ForwardRenderer.h>
#include <Window.h>

int main()
{
    // Create window
    graphics::Window* window = new graphics::Window("Title", 500, 500);

    // Create RenderManager
    graphics::RenderManager rendermanager = graphics::RenderManager(
        // Window
        window,
        // Renderers
        {
            new graphics::ForwardRenderer(
                new graphics::Program({
                    {"resources/test.vert", graphics::Shader::Type::VERTEX},
                    {"resources/test.frag", graphics::Shader::Type::FRAGMENT}
                })
            )
        }
    );

    // Load resources
    Sampler3D* moonTexture = new Sampler3D("moon.png");

    // Generate scene
    Scene scene = Scene
    {
        // Cameras and models
        new Camera{ math::vec3(0.0f, -1.0f, 0.0f), math::vec3(0.0f, 0.0f, 0.0f) },
        new Model 
        {
            // Uniforms
            {
                new UniformSampler3D("albedo", moonTexture)
            },
            // Meshes
            {
                
            }
        }
    };

    // Main loop
    while(!rendermanager.windowClosed())
    {
        // Process input
        // Render scene
        rendermanager.render();
    }
}