#include <Window.h>

#include <string>
#include <utility>

#include <Renderer.h>
#include <Input.h>

namespace graphics
{
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
                type, severity, message);
    }

    void framebufferResizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
        Renderer::getInstance()->setPerspective(std::nullopt, (float)width / (float)height, std::nullopt, std::nullopt);
    }

    // Converts position to be vertically normalized and horizontally depending on aspect ratio.
    // Also converts so that origin is in lower-left corner.
    void positionCallback(GLFWwindow* window, double xpos, double ypos)
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        Input::Mouse::positionCallback(window, (float)((xpos / width) * (width/height)), (float)(-ypos / height));
    }

    Window::Window(const std::string& title, int width, int height) : width(width), height(height)
    {        
        // Initialize GLFW
        if(!glfwInit())
            throw std::runtime_error("Failed to initialize GLFW!");
        else
            std::cout << "GLFW initialized!\n\tVersion: " << GLFW_VERSION_MAJOR << "." << GLFW_VERSION_MINOR << std::endl;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window
        this->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if(!this->window)
            throw std::runtime_error("Failed to initialize GLFW window!");
        else
            std::cout << "Initialized GLFW window!" << std::endl;


        // Configure window
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSwapInterval(0);

        // Initialize GLAD
        if(!gladLoadGL())
            throw std::runtime_error("Failed to initialize GLAD!");
        else
            std::cout << "GLAD initialized!\n\tVersion: " << GLVersion.major << "." << GLVersion.minor << std::endl;

        // Enable OpenGL debug output
        glEnable              (GL_DEBUG_OUTPUT);
        glDebugMessageCallback(DebugMessageCallback, 0);

        // Set input callbacks
        glfwSetKeyCallback(window, Input::Keyboard::keyCallback);
        glfwSetCursorPosCallback(window, positionCallback);
        glfwSetCursorEnterCallback(window, Input::Mouse::enterCallback);
        glfwSetMouseButtonCallback(window, Input::Mouse::buttonCallback);
        glfwSetScrollCallback(window, Input::Mouse::scrollCallback);
    }

    Window::~Window()
    {
        glfwTerminate();
    }

    int Window::getWidth() const { return width; }

    int Window::getHeight() const { return height; }

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
}