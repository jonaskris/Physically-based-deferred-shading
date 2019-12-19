#include <vector>
#include <iostream>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Renderer.h>

#include <Utils.h>
#include <Window.h>
#include <Scene.h>
#include <Program.h>
#include <TextureUnitManager.h>

namespace Renderer
{
    void initialize(const std::string& windowTitle, size_t windowWidth, size_t windowHeight, const std::vector<std::pair<std::string, Shader::Type>> geometryShaders/*, const std::vector<std::pair<std::string, Shader::Type>>& lightingShaders*/)
    {
        // Renderer members
        window = new Window(windowTitle, windowWidth, windowHeight);

        geometryProgram = new Program(geometryShaders);
        lightingProgram = nullptr;

        setProjection(math::Degrees(90.0f), (float)windowWidth / (float)windowHeight, 0.01f, 20.0f);

        model = {"model", math::Mat4::identity()};

        glEnable(GL_DEPTH_TEST);
        glFrontFace(GL_CCW);
        glDisable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glPointSize(3.0f);
        glClearColor(1.0f, 0.7f, 0.3f, 1.0f);
    };

    void terminate()
    {
        delete window;
        delete geometryProgram;
        delete lightingProgram;
        projection = {};
        model = {};
    };

    bool windowClosed() { return window->closed(); }

    void render(Scene* scene)
    {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw nodes
        geometryProgram->enable();

        projection.set(geometryProgram->getProgramId());
        model.set(geometryProgram->getProgramId());

        std::vector<Node*>& nodes = scene->getNodes();
        std::for_each(nodes.begin(), nodes.end(), [&](Node* node)
        {
            TextureUnitManager::pushContext();
            node->setUniforms(geometryProgram->getProgramId());
            node->draw();
            TextureUnitManager::popContext();
        });
        geometryProgram->disable();

        // Update window
        window->update();

        // Enable geometry pass program
        // Set uniforms (Projection, View, Model)
        // Bind framebuffer
        // Clear window
        // Draw
        // Unbind framebuffer
        // Disable geometry pass program
        // Clear window ?
        // Enable lighting pass program
        // Set uniforms (View, Framebuffer texture positions, lighting)
        // Bind framebuffer textures
        // Render quad
        // Disable lighting pass program
        // Update window

        // Calculate Deltatime
        double timeThisFrame = glfwGetTime();
        deltatime = timeThisFrame - timeLastFrame;
        fps = (size_t)(1.0 / deltatime);
        timeLastFrame = timeThisFrame;
    }

    size_t getFPS()
    {
        return fps;
    }

    double getDeltatime()
    {
        return deltatime;
    }

    void setProjection(math::Radians newFov, float newAspectratio, float newNear, float newFar)
    {
        if(newFov)
            fov = newFov;

        if(newAspectratio)
            aspectratio = newAspectratio;

        if(newNear)
            near = newNear;

        if(newFar)
            far = newFar;

        projection = UniformMat4f("projection", math::Mat4::perspective(fov, aspectratio, near, far));
    }

    void setModel(const math::Mat4& modelMatrix)
    {
        model.setMatrix(modelMatrix);
    }
}