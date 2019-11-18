#include <iostream>
#include <vector>
#include <Icosphere.h>
#include <Shader.h>
#include <Scene.h>
#include <Camera.h>
#include <Vec3.h>
#include <Sampler.h>
#include <Window.h>
#include <Vertex.h>
#include <Material.h>
#include <Image.h>
#include <Model.h>
#include <Renderer.h>
#include <Input.h>

int main()
{
    // Initialization
        // Create Renderer
        Renderer::initialize(
            // Window
            "Title", 500, 500,
            // Shaders
            {
                {"resources/ForwardShader.vert", Shader::Type::VERTEX}, 
                {"resources/ForwardShader.frag", Shader::Type::FRAGMENT}
            }
        );

    // Resources
        //Image* moonImage = new Image("moon.png");
    
    // Samplers
        //Sampler3D* moonSampler = new Sampler3D(*moonImage);

    // Materials
    //Material* moonMaterial = new Material(new UniformSampler3D("albedo", moonSampler));

    Mesh<CubemappedVertex>* ico = Icosphere::generate<CubemappedVertex>(2);

    std::cout << *ico << std::endl;

    Camera* camera = nullptr;

    // Generate scene
    Scene* scene = new Scene
    ({
        // Nodes
        camera = new FirstPersonCamera(math::vec3{-2.0f, 0.0f, 0.0f}, math::vec3{0.0f, 1.0f, 0.0f}, 0.0f, 0.0f),
        //camera = new Camera(math::vec3(0.0f, 0.0f, 3.0f), math::vec3(0.0f, 0.0f, 0.0f), math::vec3(0.0f, 1.0f, 0.0f)),
        new Model 
        (
            // Material
            nullptr,//moonMaterial,

            // Mesh
            ico
        )
    });

    unsigned int framecounter = 0;

    // Main loop
    while(!Renderer::windowClosed())
    {
        framecounter++;
        if(framecounter % 100 == 0)
            std::cout << "FPS: " << Renderer::getFPS() << std::endl;

        //camera->lookFrom += math::vec3{0.01f, 0.0f, 0.0f};

        Input::update(Renderer::getDeltatime()); // Process input
        Renderer::render(scene);                 // Render scene
    }
}