#pragma once

#include <utility>
#include <string>
#include <vector>
#include <Uniform.h>
#include <Shader.h>

class Program;
class Window;
class Scene;

/*
    The Renderer controls the window, performs
    once-per-frame actions such as clearing the window before rendering,
    and updating the window after rendering.
*/
namespace Renderer
{

    namespace
    {
        Window* window;
        Program* geometryProgram;
        Program* lightingProgram;

        // Projection
        UniformMat4f projection;
        float fov;
        float aspectratio;
        float near;
        float far;

        // Model
        UniformMat4f model;

        double deltatime = 0.0;
        size_t fps = 0;
        double timeLastFrame = 0; // GLFW time
    }

    void initialize(const std::string& windowTitle, size_t windowWidth, size_t windowHeight, const std::vector<std::pair<std::string, Shader::Type>> geometryShaders/*, const std::vector<std::pair<std::string, Shader::Type>> lightingShaders*/);
    void terminate();

    bool windowClosed();
    void render(Scene* scene);

    double getDeltatime();
    size_t getFPS();

    // Updates projection arguments if argument is not 0 and updates the matrix
    void setProjection(float newFov, float newAspectratio, float newNear, float newFar);
    void setModel(const math::mat4& modelMatrix);

}