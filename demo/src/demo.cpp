#include <iostream>
#include <vector>
#include <Icosphere.h>
#include <Program.h>
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

int main()
{
    // Initialization
        // Create window
        Window* window = new Window("Title", 500, 500);

        // Create shaders
        Shader* forwardVert = new Shader("resources/ForwardShader.vert", Shader::Type::VERTEX);
        Shader* forwardFrag = new Shader("resources/ForwardShader.frag", Shader::Type::FRAGMENT);

        // Create program
        Program* forwardProg  = new Program({ forwardVert, forwardFrag });

        // Create Renderer
        Renderer renderer = Renderer(
            // Window
            window,
            // Programs
            forwardProg,
            nullptr
        );

    // Resources
        //Image* moonImage = new Image("moon.png");
    
    // Samplers
        //Sampler3D* moonSampler = new Sampler3D(*moonImage);

    // Materials
    //Material* moonMaterial = new Material(new UniformSampler3D("albedo", moonSampler));

    Mesh<CubemappedVertex>* ico = new Icosphere(2);

    Camera* camera = nullptr;

    // Generate scene
    Scene* scene = new Scene
    ({
        // Nodes
        camera = new Camera(math::vec3{0.0f, -1.0f, 0.0f}, math::vec3{0.0f, 0.0f, 0.0f}, math::vec3{0.0f, 0.0f, 1.0f}, 90.0f, 500.0f/500.0f, 0.1f, 10.0f),
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
    while(!window->closed())
    {
        framecounter++;
        if(framecounter % 100 == 0)
        {
            std::cout << "On frame: " << framecounter << std::endl;
        }

        camera->lookFrom += math::vec3{0.01f, 0.0f, 0.0f};

        // Process input
        // Render scene
        renderer.render(scene);
    }
}