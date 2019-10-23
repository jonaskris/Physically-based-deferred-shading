#include <iostream>
#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace graphics
{
    void windowresize(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }
    
    Window::Window(int width, int height, const char* title)
    {
        // Initialize GLFW
        if(!glfwInit())
            std::cerr << "Failed to initialize GLFW!" << std::endl;
        else
            std::cout << "GLFW initialized!\n\tVersion: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << std::endl;
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
        // Initialize window
        this->window = glfwCreateWindow(width, height, title, NULL, NULL);
        if(!this->window)
            std::cerr << "\tFailed to initialize GLFW window!" << std::endl;
        else
            std::cout << "\tInitialized GLFW window!" << std::endl;
    
        // Configure window
        glfwMakeContextCurrent(window);
        glfwSetWindowSizeCallback(window, windowresize);
    }
    
    Window::~Window()
    {
        glfwTerminate();
    }
    
    void Window::update() const
    {
        // Poll for input
        glfwPollEvents();
    
        // Swap front buffer(displayed) and back buffer
        glfwSwapBuffers(window);
    }
    
    bool Window::closed() const
    {
        return glfwWindowShouldClose(window);
    }
}