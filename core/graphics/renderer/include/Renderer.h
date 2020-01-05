#pragma once

#include <utility>
#include <string>
#include <vector>

#include <Mat4.h>

#include <Utils.h>
#include <Shader.h>

class Program;
class Window;
class Scene;

namespace graphics
{
    class Framebuffer;
}

/*
    The Renderer controls the window, performs
    once-per-frame actions such as clearing the window before rendering,
    and updating the window after rendering.
*/
namespace Renderer
{
    namespace
    {
        // Essentials
        Window* window;
        Program* geometryProgram;
        Program* lightingProgram;
        Program* skyboxProgram;
        graphics::Framebuffer* framebuffer;
        unsigned int planeMesh; // Used for drawing screen-covering plane in lighting pass

        // Projection
            // Perspective (Geometry)
            math::Mat4 projection;
            math::Radians fov(45.0f);
            float aspectratio;
            float nearP;
            float farP;

            // Orthographic (Lighting)
            math::Mat4 orthographic;
            float left, right, bottom, top, nearO, farO;

        // Timing
        double deltatime = 0.0;
        size_t fps = 0;
        double timeLastFrame = 0; // GLFW time
    }

    void initialize(const std::string& windowTitle, size_t windowWidth, size_t windowHeight, 
        const std::vector<std::pair<std::string, Shader::Type>> geometryShaders, 
        const std::vector<std::pair<std::string, Shader::Type>> lightingShaders,
        const std::vector<std::pair<std::string, Shader::Type>> skyboxShaders);
    void terminate();

    bool windowClosed();
    void render(unsigned int sceneIdentifier);

    double getDeltatime();
    size_t getFPS();

    // Updates perspective matrix arguments if argument is not 0 and updates the matrix
    void setPerspective(std::optional<math::Radians> newFov = std::nullopt, std::optional<float> newAspectratio = std::nullopt, std::optional<float> newNear = std::nullopt, std::optional<float> newFar = std::nullopt);

    // Updates orthographic matrix arguments if argument is not 0 and updates the matrix
    void setOrthographic(std::optional<float> newLeft = std::nullopt, std::optional<float> newRight = std::nullopt, std::optional<float> newBottom = std::nullopt, std::optional<float> newTop = std::nullopt, std::optional<float> newNear = std::nullopt, std::optional<float> newFar = std::nullopt);
}