#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace graphics
{
    class Window
    {
    private:
        GLFWwindow* window = nullptr;
        
    public:
        Window(const std::string& title, int width, int height);
        ~Window();
    
        // Clear OpenGL viewport
        void clear() const;
    
        // Check for OpenGL errors and swap buffers
        void update() const;
    
        // Returns true if user closed window.
        bool closed() const;
    };
}