#include <iostream>
#include <Renderer.h>
#include <Icosphere.h>
#include <Program.h>
#include <Shader.h>

int main()
{
    // Initialize 
    graphics::Renderer renderer = graphics::Renderer(500, 500);

    geometry::Mesh<geometry::CubemappedVertex>* testMesh = new geometry::Icosphere(1);

    std::cout << *testMesh << std::endl;

    graphics::Program* testProgram = new graphics::Program({
        {"test.vert", graphics::Shader::Type::VERTEX},
        {"test.frag", graphics::Shader::Type::FRAGMENT}
    });

    // Main loop
    while(!renderer.windowClosed())
    {
        // Process input
        renderer.render();
    }
}