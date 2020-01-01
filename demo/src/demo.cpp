#include <iostream>
#include <vector>

#include <Utils.h>
#include <Vec3.h>
#include <Icosphere.h>
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
                {"resources/ForwardShader.vert", Shader::Type::VERTEX}, 
                {"resources/ForwardShader.frag", Shader::Type::FRAGMENT}
            }
        );



    // Initialize scene
    {
        // Images
        //Image* moonImage = new Image("resources/moon.png");
        Image* metalAlbedo = new Image("resources/metal-albedo.png");

        // Textures
        //unsigned int moonTexture = graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( new graphics::TextureCubemap(*moonImage) );
        unsigned int metalAlbedoTexture = graphics::RenderData::insert<graphics::TextureCubemap, graphics::Texture>( new graphics::TextureCubemap(*metalAlbedo) );

        //// Materials
        //unsigned int moonMaterial = graphics::RenderData::insert<graphics::Material>( new graphics::Material(moonTexture) );
        unsigned int metalMaterial = graphics::RenderData::insert<graphics::Material>( new graphics::Material(metalAlbedoTexture) );

        // Meshes
        unsigned int icosphere = Icosphere::generate(2);

        // Nodes
        unsigned int cam = graphics::RenderData::insert<graphics::FirstPersonCamera, graphics::Node>( new graphics::FirstPersonCamera(math::Vec3{-2.0f, 0.0f, 0.0f}, math::Vec3{0.0f, 1.0f, 0.0f}, math::Degrees(0.0f), math::Degrees(0.0f)) );
        unsigned int mod = graphics::RenderData::insert<graphics::Model, graphics::Node>( new graphics::Model(icosphere, metalMaterial) );

        // Scenes
        unsigned int s = graphics::RenderData::insert<graphics::Scene>( new graphics::Scene({cam, mod}) );
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