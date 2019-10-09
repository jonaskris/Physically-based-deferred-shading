#include <iostream>
#include <glad/glad.h>
#include <Window.h>

int main()
{
    // Initialize 
    Window window = Window(500, 500, "Tittel");

    // Main loop
    while(!window.closed())
    {
        // Process input
        // Render
        window.update();
    }
}