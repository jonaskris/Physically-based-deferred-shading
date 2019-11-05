#include <iostream>
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void GLAPIENTRY
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}

void windowresize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(const std::string& title, int width, int height)
{        
    // Initialize GLFW
    if(!glfwInit())
        std::cerr << "Failed to initialize GLFW!" << std::endl;
    else
        std::cout << "GLFW initialized!\n\tVersion: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << std::endl;
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if(!this->window)
        std::cerr << "\tFailed to initialize GLFW window!" << std::endl;
    else
        std::cout << "\tInitialized GLFW window!" << std::endl;

    // Configure window
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, windowresize);

    // Initialize GLAD
    if(!gladLoadGL())
        std::cerr << "Failed to initialize GLAD!" << std::endl;
    else
        std::cout << "GLAD initialized!\n\tVersion: " << GLVersion.major << "." << GLVersion.minor << std::endl;

    // During init, enable debug output
    glEnable              ( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 );
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