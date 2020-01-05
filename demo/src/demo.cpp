#include <iostream>
#include <vector>

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
        Image moonImage("resources/moon.png");
        Image metalAlbedo("resources/metal-albedo.png");

        Image skyboxLF("resources/skybox_lf.tga");
        Image skyboxRT("resources/skybox_rt.tga");
        Image skyboxDN("resources/skybox_dn.tga");
        Image skyboxUP("resources/skybox_up.tga");
        Image skyboxFT("resources/skybox_ft.tga");
        Image skyboxBK("resources/skybox_bk.tga");

        // Textures
        unsigned int moonTexture = graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( new graphics::TextureCubemap(moonImage) );
        unsigned int metalAlbedoTexture = graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( new graphics::TextureCubemap(metalAlbedo) );
        unsigned int skyboxTexture = graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( 
            new graphics::TextureCubemap(skyboxLF, skyboxRT, skyboxBK, skyboxFT, skyboxUP, skyboxDN) 
            );

        // Materials
        unsigned int moonMaterial = graphics::RenderData::insert<graphics::Material>( new graphics::Material(moonTexture) );
        unsigned int metalMaterial = graphics::RenderData::insert<graphics::Material>( new graphics::Material(metalAlbedoTexture) );
        unsigned int skyboxMaterial = graphics::RenderData::insert<graphics::Material>( new graphics::Material(skyboxTexture) );

        // Meshes
        unsigned int icosphere = Icosphere::generate(2);
        unsigned int cubeCubemapped = Cube::generate(true); // True: cubemapped
        //unsigned int plane = Plane::generate();

        // Nodes
        unsigned int cam = graphics::RenderData::insert<graphics::FirstPersonCamera, graphics::Node>( new graphics::FirstPersonCamera(math::Vec3{-2.0f, 0.0f, 0.0f}, math::Degrees(0.0f), math::Degrees(0.0f), {}) );
        unsigned int skybox = graphics::RenderData::insert<graphics::Model, graphics::Node>( new graphics::Model(cubeCubemapped, skyboxMaterial, {}, {}) );
        unsigned int mod2 = graphics::RenderData::insert<graphics::Model, graphics::Node>( new graphics::Model(icosphere, moonMaterial, math::Transform({0.75f, 0.0f, 0.0f}, {}, {0.5f, 0.5f, 0.5f}), {}) );
        unsigned int mod1 = graphics::RenderData::insert<graphics::Model, graphics::Node>( new graphics::Model(icosphere, metalMaterial, {}, {mod2}) );
        unsigned int mod3 = graphics::RenderData::insert<graphics::Model, graphics::Node>( new graphics::Model(cubeCubemapped, metalMaterial, math::Transform({-1.0f, 0.0f, 0.0f}, {}), {}) );

        // Scenes
        unsigned int s = graphics::RenderData::insert<graphics::Scene>( new graphics::Scene(cam, skybox, {mod1, mod3}) );
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