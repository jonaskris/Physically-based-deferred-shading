#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Renderer.h>
#include <Framebuffer.h>

#include <Utils.h>
#include <Window.h>
#include <Scene.h>
#include <Program.h>
#include <TextureUnitManager.h>
#include <RenderData.h>
#include <Node.h>
#include <Texture.h>
#include <Mesh.h>
#include <Uniform.h>
#include <Model.h>
#include <Camera.h>
#include <Mat4.h>
#include <Plane.h>
#include <Cube.h>

namespace Renderer
{
    void initialize(const std::string& windowTitle, size_t windowWidth, size_t windowHeight, 
        const std::vector<std::pair<std::string, Shader::Type>> geometryShaders, 
        const std::vector<std::pair<std::string, Shader::Type>> lightingShaders, 
        const std::vector<std::pair<std::string, Shader::Type>> skyboxShaders)
    {
        // Essentials
        window = new Window(windowTitle, windowWidth, windowHeight);
        geometryProgram = new Program(geometryShaders);
        lightingProgram = new Program(lightingShaders);
        skyboxProgram = new Program(skyboxShaders);
        framebuffer = new graphics::Framebuffer(windowWidth, windowHeight);
        planeMesh = Plane::generate();

        // Default perspective
        fov = math::Degrees(45.0f);
        aspectratio = (float)windowWidth / (float)windowHeight;
        nearP = 0.01f;
        farP = 20.0f;
        setPerspective();

        // Default orthographic
        left = -1.0f;
        right = 1.0f;
        bottom = -1.0f;
        top = 1.0f;
        nearO = -1.0f;
        farO = 1.0f;
        setOrthographic();

        glEnable(GL_DEPTH_TEST);
        glFrontFace(GL_CCW);
        glEnable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glPointSize(3.0f);
        glClearColor(1.0f, 0.7f, 0.3f, 1.0f);
    };

    void terminate()
    {
        delete window;
        delete geometryProgram;
        delete lightingProgram;
        delete framebuffer;
        projection = {};
    };

    bool windowClosed() { return window->closed(); }

    void render(unsigned int sceneIdentifier)
    {
// Geometry
        // Bind framebuffer
        framebuffer->bind();

        // Clear framebuffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable geometry pass program
        geometryProgram->enable();
        GLuint programId = geometryProgram->getProgramId();

        // Set uniforms
        Uniform::setMat4(programId, "projection", projection);
        Uniform::setMat4(programId, "view", math::Mat4::identity());
        Uniform::setMat4(programId, "model", math::Mat4::identity());

        // Draw geometry
        graphics::Scene* scene = graphics::RenderData::get<graphics::Scene>(sceneIdentifier);
        graphics::FirstPersonCamera* camera = graphics::RenderData::get<graphics::FirstPersonCamera>(scene->camera);
        graphics::Model* skybox = graphics::RenderData::get<graphics::Model>(scene->skybox);
        camera->process(programId);
        for(unsigned int n : scene->nodes)
        {
            graphics::Node* node = graphics::RenderData::get<graphics::Model>(n);
                        
            if(node)
                node->process(programId);
            else
                std::cout << "Couldent find node!" << std::endl;
        }

        // Unbind framebuffer
        framebuffer->unbind();

        // Disable geometry pass program
        geometryProgram->disable();
        
// Lighting
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable lighting pass program
        lightingProgram->enable();
        programId = lightingProgram->getProgramId();

        // Set orthographic projection
        Uniform::setMat4(programId, "projection", orthographic);

        // Push texture unit context
        TextureUnitManager::pushContext();

        // Bind framebuffer textures
        Uniform::setTexture2D(programId, "gPosition", framebuffer->position->getId());
        Uniform::setTexture2D(programId, "gNormal", framebuffer->normal->getId());
        Uniform::setTexture2D(programId, "gAlbedo", framebuffer->albedo->getId());

        // Draw screen-wide quad
        Uniform::setMat4(programId, "model", math::Mat4::scale({2.0f, 2.0f, 2.0f}));
        graphics::Mesh* quad = graphics::RenderData::get<graphics::Mesh>(planeMesh);
        quad->draw();
        
        // Pop texture unit context
        TextureUnitManager::popContext();

        // Disable lighting pass program
        lightingProgram->disable();

// Skybox
        // Set depth func to less than or equal
        glDepthFunc(GL_LEQUAL);

        // Set face culling to front
        glCullFace(GL_FRONT);

        // Blit (copy) framebuffer depth to main buffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer->getId());
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, 1000, 1000, 0, 0, 1000, 1000, GL_DEPTH_BUFFER_BIT, GL_NEAREST);

            // Enable skybox pass program
            skyboxProgram->enable();
            programId = skyboxProgram->getProgramId();

            // Set uniforms
            Uniform::setMat4(programId, "projection", projection);
            Uniform::setMat4(programId, "view", camera->getView().removeTranslation());
            Uniform::setMat4(programId, "model", math::Mat4::identity());

                // Push texture unit context
                TextureUnitManager::pushContext();
                
                // Draw skybox geometry
                skybox->process(programId);

                // Pop texture unit context
                TextureUnitManager::popContext();

            // Disable skybox pass program
            skyboxProgram->disable();

        // Set face culling to back (Default)
        glCullFace(GL_BACK);

        // Set depth func to less than (Default)
        glDepthFunc(GL_LESS);

// Finalization
        // Update window 
        window->update();

        // Update timing
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

    void setPerspective(std::optional<math::Radians> newFov, std::optional<float> newAspectratio, std::optional<float> newNear, std::optional<float> newFar)
    {
        if(newFov)
            fov = newFov.value();
        if(newAspectratio)
            aspectratio = newAspectratio.value();
        if(newNear)
            nearP = newNear.value();
        if(newFar)
            farP = newFar.value();

        projection = math::Mat4::perspective(fov, aspectratio, nearP, farP);
    }

    // Updates orthographic matrix arguments if argument is not 0 and updates the matrix
    void setOrthographic(std::optional<float> newLeft, std::optional<float> newRight, std::optional<float> newBottom, std::optional<float> newTop, std::optional<float> newNear, std::optional<float> newFar)
    {
        if(newLeft)
            left = newLeft.value();
        if(newRight)
            right = newRight.value();
        if(newBottom)
            bottom = newBottom.value();
        if(newTop)
            top = newTop.value();
        if(newNear)
            nearO = newNear.value();
        if(newFar)
            farO = newFar.value();

        orthographic = math::Mat4::orthographic(left, right, bottom, top, nearO, farO);
    }
}