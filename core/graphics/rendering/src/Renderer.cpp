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


Renderer::Renderer(Window* window, const std::vector<std::pair<std::string, Shader::Type>> geometryShaders/*, const std::vector<std::pair<std::string, Shader::Type>>& lightingShaders*/)
    : window(window), geometryProgram(new Program(geometryShaders)), lightingProgram(nullptr), 
    projection({"projection", math::mat4::perspective(80.0f, 500.0f/500.0f, 0.01f, 20.0f)}),
    model({"model", math::mat4::identity()})
{
    glDisable(GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glDisable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glPointSize(3.0f);
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

    //Check for OpenGL errors
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

void Renderer::setProjection(float fov, float aspectratio, float near, float far)
{
    projection = UniformMat4f("projection", math::mat4::perspective(fov, aspectratio, near, far));
}