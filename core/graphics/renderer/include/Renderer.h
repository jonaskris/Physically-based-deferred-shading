#pragma once

#include <utility>
#include <string>

#include <Vec3.h>
#include <Mat4.h>

#include <DataIdentifier.h>
#include <Utils.h>
#include <Mesh.h>

#include <Framebuffer.h>

/*
    The Renderer controls the window, performs
    once-per-frame actions such as clearing the window before rendering,
    and updating the window after rendering.
*/
namespace graphics
{
    class Window;
    class Scene;

    enum class RenderMode { DEFAULT = 0, ALBEDO = 1, NORMALS = 2, METALLNESS = 3, ROUGHNESS = 4, FRESNEL = 5, IRRADIANCE = 6, REFLECTION = 7, POSITION = 8};

    class Renderer
    {
    private:
        static Renderer* instance;

    private:
        // Essentials
        Window* window;
        graphics::Framebuffer* framebuffer;

        // Projection
            // Perspective (Geometry)
            math::Mat4 projection;
            math::Radians fov = math::Radians(45.0f);
            float aspectratio;
            float nearP;
            float farP;

        // Temporary light
        math::Vec3 lightPosition{0.0f, 2.0f, -3.0f};
        math::Vec3 lightColor{50.0f, 50.0f, 50.0f};

        // Meshes
            // Plane mesh for drawing screen wide quad
            DataIdentifier<Mesh> planeMesh;

            // Orthographic (Lighting)
            math::Mat4 orthographic;
            float left, right, bottom, top, nearO, farO;

        // Timing
        double deltatime = 0.0;
        size_t fps = 0;
        double timeLastFrame = 0; // GLFW time

        Renderer(const std::string& windowTitle, size_t windowWidth, size_t windowHeight);

    public:
        ~Renderer();

        static Renderer* init(const std::string& windowTitle, size_t windowWidth, size_t windowHeight);

        static Renderer* getInstance();

        bool windowClosed();
        void render(DataIdentifier<Scene> sceneIdentifier, RenderMode rendermode);

        double getDeltatime();
        size_t getFPS();

        // Updates perspective matrix arguments if argument is not 0 and updates the matrix
        void setPerspective(std::optional<math::Radians> newFov = std::nullopt, std::optional<float> newAspectratio = std::nullopt, std::optional<float> newNear = std::nullopt, std::optional<float> newFar = std::nullopt);

        // Updates orthographic matrix arguments if argument is not 0 and updates the matrix
        void setOrthographic(std::optional<float> newLeft = std::nullopt, std::optional<float> newRight = std::nullopt, std::optional<float> newBottom = std::nullopt, std::optional<float> newTop = std::nullopt, std::optional<float> newNear = std::nullopt, std::optional<float> newFar = std::nullopt);    
    };
}