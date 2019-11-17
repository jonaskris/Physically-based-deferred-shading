#include <iostream>
#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Input.h>

void GLAPIENTRY
DebugMessageCallback( GLenum source,
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

void windowResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Converts position to be vertically normalized and horizontally depending on aspect ratio.
// Also converts so that origin is in lower-left corner.
void positionCallback(GLFWwindow* window, double xpos, double ypos)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    MouseCallback::positionCallback(window, (float)((xpos / width) * (width/height)), (float)(-ypos / height));
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
    glfwSetFramebufferSizeCallback(window, windowResizeCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialize GLAD
    if(!gladLoadGL())
        std::cerr << "Failed to initialize GLAD!" << std::endl;
    else
        std::cout << "GLAD initialized!\n\tVersion: " << GLVersion.major << "." << GLVersion.minor << std::endl;

    // Enable OpenGL debug output
    glEnable              (GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugMessageCallback, 0);

    // Set input callbacks
    glfwSetKeyCallback(window, KeyboardCallback::keyCallback);
    glfwSetCursorPosCallback(window, positionCallback);
    glfwSetCursorEnterCallback(window, MouseCallback::enterCallback);
    glfwSetMouseButtonCallback(window, MouseCallback::buttonCallback);
    glfwSetScrollCallback(window, MouseCallback::scrollCallback);
}

Window::~Window()
{
    glfwTerminate();
}

void Window::update() const
{
    // Swap front buffer(displayed) and back buffer
    glfwSwapBuffers(window);

    // Poll for input
    glfwPollEvents();
}

bool Window::closed() const
{
    return glfwWindowShouldClose(window);
}