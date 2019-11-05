#include <vector>
#include <iostream>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Renderer.h>
#include <Window.h>
#include <Scene.h>
#include <Program.h>
#include <TextureUnitManager.h>


Renderer::Renderer(Window* window, Program* geometryProgram, Program* lightingProgram) : window(window), geometryProgram(geometryProgram), lightingProgram(lightingProgram) 
{
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glClearColor(1.0f, 0.7f, 0.3f, 1.0f);
};

Renderer::~Renderer()
{

};

bool Renderer::windowClosed() const { return window->closed(); }

void Renderer::render(Scene* scene)
{
    // Clear window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw nodes
    geometryProgram->enable();

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

    // Check for OpenGL errors
    //GLenum error = glGetError();
    //if(error != GL_NO_ERROR)
    //    std::cout << "OpenGL error: " << error << std::endl;

    
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
}