#include <iostream>
#include <vector>
#include <array>

#include <Utils.h>
#include <Vec3.h>

#include <Shader.h>
#include <Program.h>
#include <Window.h>
#include <Renderer.h>
#include <Input.h>
#include <DataStore.h>
#include <Mesh.h>

#include <Geometry.h>
#include <Icosphere.h>
#include <Cube.h>
#include <Plane.h>

//#include <Image.h>
//#include <Texture.h>
//#include <Material.h>

// For constructing scene
#include <Scene.h>
#include <Node.h>
//#include <Model.h>
#include <Camera.h>

#include <DrawKey.h>
#include <AssimpLoader.h>
#include <ProgramStore.h>
#include <DrawUnit.h>
#include <ProgramRequirement.h>
#include <Defines.h>
#include <GeometryProgramGenerator.h>
#include <Shader.h>
#include <Source.h>
#include <Skybox.h>

int main()
{
    // Initialization
        // Initialize Renderer
        graphics::Renderer* renderer = graphics::Renderer::init
        (
            // Window
            "Title", 1000, 1000
        );

        // Create programs/shaders
        graphics::ProgramStore::setGeometryProgram( new graphics::Program(
            std::vector<graphics::Shader>{
                graphics::Shader::loadShader("resources/shaders/Geometry.vert", graphics::ShaderType::VERTEX), 
                graphics::Shader::loadShader("resources/shaders/Geometry.frag", graphics::ShaderType::FRAGMENT)
            }
        ));

        graphics::ProgramStore::setLightingProgram(new graphics::Program(
            std::vector<graphics::Shader>{
                graphics::Shader::loadShader("resources/shaders/Lighting.vert", graphics::ShaderType::VERTEX), 
                graphics::Shader::loadShader("resources/shaders/Lighting.frag", graphics::ShaderType::FRAGMENT)
            }
        ));

        graphics::ProgramStore::setSkyboxProgram(new graphics::Program(
            std::vector<graphics::Shader>{
                graphics::Shader::loadShader("resources/shaders/Skybox.vert", graphics::ShaderType::VERTEX), 
                graphics::Shader::loadShader("resources/shaders/Skybox.frag", graphics::ShaderType::FRAGMENT)
            }
        ));

        graphics::ProgramStore::setIrradianceMapProgram(new graphics::Program(
            std::vector<graphics::Shader>{
                graphics::Shader::loadShader("resources/shaders/IrradianceMap.vert", graphics::ShaderType::VERTEX), 
                graphics::Shader::loadShader("resources/shaders/IrradianceMap.frag", graphics::ShaderType::FRAGMENT)
            }
        ));

        graphics::ProgramStore::setPrefilterMapProgram(new graphics::Program(
            std::vector<graphics::Shader>{
                graphics::Shader::loadShader("resources/shaders/PrefilterMap.vert", graphics::ShaderType::VERTEX), 
                graphics::Shader::loadShader("resources/shaders/PrefilterMap.frag", graphics::ShaderType::FRAGMENT)
            }
        ));

        graphics::ProgramStore::setBrdfLUTProgram(new graphics::Program(
            std::vector<graphics::Shader>{
                    graphics::Shader::loadShader("resources/shaders/BrdfLUT.vert", graphics::ShaderType::VERTEX), 
                    graphics::Shader::loadShader("resources/shaders/BrdfLUT.frag", graphics::ShaderType::FRAGMENT)
                }
        ));

    DataIdentifier<graphics::Scene> scene;

    // Initialize scene
    {
        graphics::Scene* sceneP = new graphics::Scene(
            new graphics::FPSCamera({0.0f, 0.0f, 3.0f}, math::Radians(0.0f), math::Radians(0.0f)),
            graphics::Skybox(
                DataStore::insert<graphics::Texture>(
                    new graphics::TextureCubemap(
                    {
                        {"resources/images/skybox1/right.jpg"},
                        {"resources/images/skybox1/left.jpg"},
                        {"resources/images/skybox1/top.jpg"},
                        {"resources/images/skybox1/bottom.jpg"},
                        {"resources/images/skybox1/front.jpg"},
                        {"resources/images/skybox1/back.jpg"}
                    }
                    )
                )
            ),
            std::vector<graphics::Node>{}
        );

        graphics::loadNode(sceneP->nodes, Source("resources/models/GreenToyDinosaur/GreenToyDinosaur.gltf"));
        sceneP->nodes.back().transform = math::Transform({}, {}, {0.1f, 0.1f, 0.1f});
        graphics::loadNode(sceneP->nodes, Source("resources/models/WoodFloor/WoodFloor.gltf"));
        sceneP->nodes.back().transform = math::Transform({0.0, -0.1, 0.0}, {}, {1.0f, 0.1f, 1.0f});
        //sceneP->nodes.back().transform = math::Transform({}, {}, {0.001f, 0.001f, 0.001f});
        
        scene = DataStore::insert<graphics::Scene>(sceneP);
    }    

    // Main loop
    unsigned int framecounter = 0;
    while(!renderer->windowClosed())
    {
        framecounter++;
        if(framecounter % 100 == 0)
            std::cout << "FPS: " << renderer->getFPS() << std::endl;

        Input::update(renderer->getDeltatime());    // Process input

        renderer->render(scene, graphics::RenderMode::DEFAULT);
    }
}