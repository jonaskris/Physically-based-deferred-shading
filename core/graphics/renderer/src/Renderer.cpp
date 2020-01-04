#include <vector>
#include <queue>
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
#include <RenderData.h>
#include <Node.h>
#include <Texture.h>
#include <Mesh.h>
#include <Uniform.h>
#include <Model.h>
#include <Camera.h>
#include <Mat4.h>

namespace Renderer
{
    void initialize(const std::string& windowTitle, size_t windowWidth, size_t windowHeight, const std::vector<std::pair<std::string, Shader::Type>> geometryShaders/*, const std::vector<std::pair<std::string, Shader::Type>>& lightingShaders*/)
    {
        // Renderer members
        window = new Window(windowTitle, windowWidth, windowHeight);

        geometryProgram = new Program(geometryShaders);
        lightingProgram = nullptr;

        setProjection(math::Degrees(90.0f), (float)windowWidth / (float)windowHeight, 0.01f, 20.0f);

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
    };

    bool windowClosed() { return window->closed(); }

    void render(unsigned int sceneIdentifier)
    {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw nodes
        geometryProgram->enable();
        GLuint programId = geometryProgram->getProgramId();

        // Set uniforms
        Uniform::setMat4(programId, "projection", projection);
        Uniform::setMat4(programId, "view", math::Mat4::identity());
        Uniform::setMat4(programId, "model", math::Mat4::identity());

        graphics::Scene* scene = graphics::RenderData::get<graphics::Scene>(sceneIdentifier);

        for(unsigned int n : scene->nodes)
        {
            graphics::Node* node = graphics::RenderData::get<graphics::Model>(n);
            if(!node)
                node = graphics::RenderData::get<graphics::FirstPersonCamera>(n);
                        
            if(node)
                node->process(programId);
            else
                std::cout << "Couldent find node!" << std::endl;
        }

        

        //std::cout << "BREAKPOINT 4" << std::endl;
        //std::cin.get();
        //std::queue<unsigned int> renderQueue;
        //for(auto e : scene->nodes)
        //    renderQueue.push(e);
        //
        //while(!renderQueue.empty())
        //{
        //    graphics::Node* node = graphics::RenderData::get<graphics::Node>(renderQueue.front());
        //    //for(auto e : node.childrenNodes)
        //    //    renderQueue.push(e);
        //    
        //    graphics::Mesh* me = graphics::RenderData::get<graphics::Mesh>(node->mesh);
        //    node->transform.set(geometryProgram->getProgramId());
        //    me->draw();
        //}

        // For every node in scene
            // Set node uniforms (Projection-, model-, and viewmatrix)(Material)
                // Set projection and view
                // Add model to stack. 
                // Set material
            // Draw node
                // Draw mesh

        //std::for_each(nodes.begin(), nodes.end(), [&](Node* node)
        //{
        //    TextureUnitManager::pushContext();
        //    node->setUniforms(geometryProgram->getProgramId());
        //    node->draw();
        //    TextureUnitManager::popContext();
        //});
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

        projection = math::Mat4::perspective(fov, aspectratio, near, far);
    }
}