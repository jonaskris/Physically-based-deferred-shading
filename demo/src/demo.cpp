#include <iostream>
#include <vector>
#include <array>

#include <Utils.h>
#include <Vec3.h>
#include <Icosphere.h>
#include <Plane.h>
#include <Cube.h>
//#include <Quaternion.h>

#include <Shader.h>
#include <Window.h>
#include <Renderer.h>
#include <Input.h>
#include <RenderData.h>

#include <Image.h>
#include <Texture.h>
#include <Material.h>

// For constructing scene
#include <Scene.h>
#include <Node.h>
#include <Model.h>
#include <Camera.h>

int main()
{
    // Initialization
        // Create Renderer
        Renderer::initialize(
            // Window
            "Title", 1000, 1000,
            // Shaders
            {
                {"resources/Shaders/Geometry.vert", Shader::Type::VERTEX}, 
                {"resources/Shaders/Geometry.frag", Shader::Type::FRAGMENT}
            },
            {
                {"resources/Shaders/Lighting.vert", Shader::Type::VERTEX}, 
                {"resources/Shaders/Lighting.frag", Shader::Type::FRAGMENT}
            },
            {
                {"resources/Shaders/Skybox.vert", Shader::Type::VERTEX}, 
                {"resources/Shaders/Skybox.frag", Shader::Type::FRAGMENT}
            }
        );

    // Initialize scene
    {
        // Images
        std::array<Image, 3> metalImages =
        {
            Image("resources/images/metal/albedo.png"),
            Image("resources/images/metal/roughness.png", 1),
            Image("resources/images/metal/metalness.png", 1)
        };

        std::array<Image, 3> plankImages =
        {
            Image("resources/images/planks/albedo.png"),
            Image("resources/images/planks/roughness.png", 1),
            Image("resources/images/planks/metalness.png", 1)
        };

        std::array<Image, 6> skyboxImages =
        {
            Image("resources/images/skybox/left.tga"),  // Left
            Image("resources/images/skybox/right.tga"), // Right
            Image("resources/images/skybox/back.tga"),  // Back
            Image("resources/images/skybox/front.tga"), // Front
            Image("resources/images/skybox/up.tga"),    // Up
            Image("resources/images/skybox/down.tga")   // Down
        };

        // Textures
        std::array<unsigned int, 3> metalTextures
        {
            graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( new graphics::TextureCubemap(metalImages[0]) ),
            graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( new graphics::TextureCubemap(metalImages[1], GL_RED) ),
            graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( new graphics::TextureCubemap(metalImages[2], GL_RED) )
        };

        std::array<unsigned int, 3> plankTextures
        {
            graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( new graphics::TextureCubemap(plankImages[0]) ),
            graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( new graphics::TextureCubemap(plankImages[1], GL_RED) ),
            graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( new graphics::TextureCubemap(plankImages[2], GL_RED) )
        };

        unsigned int skyboxTexture = graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( 
            new graphics::TextureCubemap(skyboxImages[0], skyboxImages[1], skyboxImages[2], skyboxImages[3], skyboxImages[4], skyboxImages[5]) 
        );

        // Materials
        unsigned int metalMaterial = graphics::RenderData::insert<graphics::Material>( new graphics::Material(metalTextures[0], metalTextures[1], metalTextures[2]) );
        unsigned int plankMaterial = graphics::RenderData::insert<graphics::Material>( new graphics::Material(plankTextures[0], plankTextures[1], plankTextures[2]) );
        
        unsigned int skyboxMaterial = graphics::RenderData::insert<graphics::Material>( new graphics::Material(skyboxTexture) );

        // Meshes
        unsigned int icosphere = Icosphere::generate(4);
        unsigned int cubeCubemapped = Cube::generate(true); // True: cubemapped

        // Nodes
        unsigned int cam = graphics::RenderData::insert<graphics::FirstPersonCamera, graphics::Node>( new graphics::FirstPersonCamera(math::Vec3{-2.0f, 0.0f, 0.0f}, math::Degrees(0.0f), math::Degrees(0.0f), {}) );
        unsigned int skybox = graphics::RenderData::insert<graphics::Model, graphics::Node>( new graphics::Model(cubeCubemapped, skyboxMaterial, {}, {}) );
        unsigned int mod2 = graphics::RenderData::insert<graphics::Model, graphics::Node>( new graphics::Model(icosphere, metalMaterial, math::Transform({0.75f, 0.0f, 0.0f}, {}, {0.5f, 0.5f, 0.5f}), {}) );
        unsigned int mod1 = graphics::RenderData::insert<graphics::Model, graphics::Node>( new graphics::Model(icosphere, plankMaterial, math::Transform({}, {}, {0.5f, 0.5f, 0.5f}), {mod2}) );
        unsigned int mod3 = graphics::RenderData::insert<graphics::Model, graphics::Node>( new graphics::Model(cubeCubemapped, metalMaterial, math::Transform({-1.0f, 0.0f, 0.0f}, {}), {}) );

        // Scenes
        unsigned int s = graphics::RenderData::insert<graphics::Scene>( new graphics::Scene(cam, skybox, {mod1, mod2, mod3}) );
    }

    // Main loop
    unsigned int framecounter = 0;
    while(!Renderer::windowClosed())
    {
        framecounter++;
        if(framecounter % 100 == 0)
            std::cout << "FPS: " << Renderer::getFPS() << std::endl;

        Input::update(Renderer::getDeltatime());    // Process input
        Renderer::render(1);                        // Render scene 1
    }
}