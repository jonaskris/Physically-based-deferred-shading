#include <DeferredRenderer.h>
#include <glad/glad.h>

namespace graphics
{

    DeferredRenderer::DeferredRenderer(size_t width, size_t height) : framebuffer(new Framebuffer(width, height)) {};

    DeferredRenderer::~DeferredRenderer() { delete framebuffer; };

    void DeferredRenderer::render() override
    {
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
}