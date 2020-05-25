#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace graphics
{
    class Window
    {
    private:
        GLFWwindow* window = nullptr;
        int width, height;
        
    public:
        Window(const std::string& title, int width, int height);
        ~Window();
    
        int getWidth() const;
        int getHeight() const;

        // Clear OpenGL viewport
        void clear() const;
    
        // Check for OpenGL errors and swap buffers
        void update() const;
    
        // Returns true if user closed window.
        bool closed() const;
    };
}