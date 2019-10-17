#include <iostream>
#include <Renderer.h>

int main()
{
    // Initialize 
    graphics::Renderer renderer = graphics::Renderer(500, 500);

    // Main loop
    while(!renderer.windowClosed())
    {
        // Process input
        renderer.render();
    }
}