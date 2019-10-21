#include <iostream>
#include <Icosphere.h>
#include <Program.h>
#include <Shader.h>
#include <RenderManager.h>

int main()
{
    // Initialize 
    graphics::RenderManager rendermanager = graphics::RenderManager(500, 500, {});

    //geometry::Mesh<geometry::CubemappedVertex>* testMesh = new geometry::Icosphere(1);

    //std::cout << *testMesh << std::endl;

    graphics::Program* testProgram = new graphics::Program({
        {"resources/test.vert", graphics::Shader::Type::VERTEX},
        {"resources/test.frag", graphics::Shader::Type::FRAGMENT}
    });

    // Main loop
    while(!rendermanager.windowClosed())
    {
        // Process input
        rendermanager.render();
    }
}