#include <iostream>
#include <vector>

#include <Utils.h>
#include <Vec3.h>

#include <Defines.h>
#include <Source.h>

#include <Window.h>
#include <Renderer.h>
#include <Program.h>
#include <Shader.h>
#include <Input.h>

#include <Geometry.h>
#include <Icosphere.h>
#include <Cube.h>
#include <Plane.h>
#include <Transform.h>

#include <Scene.h>
#include <Camera.h>
#include <Mesh.h>
#include <Skybox.h>
#include <AssimpLoader.h>

#include <DataStore.h>
#include <ProgramStore.h>
#include <DrawKey.h>
#include <DrawUnit.h>

int main()
{
    // Initialization
        // Initialize Renderer
        graphics::Renderer* renderer = graphics::Renderer::init
        (
            // Window
            "Physically based deferred shading", 1000, 1000
        );

        // Create programs/shaders
        graphics::ProgramStore::setProgram(defines::ProgramType::GEOMETRY, new graphics::Program(
            std::vector<graphics::Shader>{
                graphics::Shader::loadShader("resources/shaders/Geometry.vert", defines::ShaderType::VERTEX), 
                graphics::Shader::loadShader("resources/shaders/Geometry.frag", defines::ShaderType::FRAGMENT)
            }
        ));

        graphics::ProgramStore::setProgram(defines::ProgramType::LIGHTING, new graphics::Program(
            std::vector<graphics::Shader>{
                graphics::Shader::loadShader("resources/shaders/Lighting.vert", defines::ShaderType::VERTEX), 
                graphics::Shader::loadShader("resources/shaders/Lighting.frag", defines::ShaderType::FRAGMENT)
            }
        ));

        graphics::ProgramStore::setProgram(defines::ProgramType::SKYBOX, new graphics::Program(
            std::vector<graphics::Shader>{
                graphics::Shader::loadShader("resources/shaders/Skybox.vert", defines::ShaderType::VERTEX), 
                graphics::Shader::loadShader("resources/shaders/Skybox.frag", defines::ShaderType::FRAGMENT)
            }
        ));

        graphics::ProgramStore::setProgram(defines::ProgramType::IRRADIANCEMAP, new graphics::Program(
            std::vector<graphics::Shader>{
                graphics::Shader::loadShader("resources/shaders/IrradianceMap.vert", defines::ShaderType::VERTEX), 
                graphics::Shader::loadShader("resources/shaders/IrradianceMap.frag", defines::ShaderType::FRAGMENT)
            }
        ));

        graphics::ProgramStore::setProgram(defines::ProgramType::PREFILTERMAP, new graphics::Program(
            std::vector<graphics::Shader>{
                graphics::Shader::loadShader("resources/shaders/PrefilterMap.vert", defines::ShaderType::VERTEX), 
                graphics::Shader::loadShader("resources/shaders/PrefilterMap.frag", defines::ShaderType::FRAGMENT)
            }
        ));

        graphics::ProgramStore::setProgram(defines::ProgramType::BRDFLUT, new graphics::Program(
            std::vector<graphics::Shader>{
                    graphics::Shader::loadShader("resources/shaders/BrdfLUT.vert", defines::ShaderType::VERTEX), 
                    graphics::Shader::loadShader("resources/shaders/BrdfLUT.frag", defines::ShaderType::FRAGMENT)
                }
        ));

    DataIdentifier<graphics::Scene> scene;

    // Initialize scene
    {
        graphics::Scene* sceneP = new graphics::Scene(
            //new graphics::FPSCamera({0.0f, 0.0f, 3.0f}, math::Radians(0.0f), math::Radians(0.0f)),
            new graphics::AnimatedCamera(
                [](double time) -> math::Transform
                {
                    const float radius = 7.0f;
                    const float circleTime = 10.0f;
                    const float height = 1.0f;
                    float circleProgress = fmodf(time, circleTime) / circleTime;
                    math::Radians circleRad(circleProgress * math::toRadians(360.0f));

                    math::Vec3 position(sin(circleRad.radians) * radius, height, cos(circleRad.radians) * radius);

                    return math::Transform(position, math::Quaternion::fromAxisAngle({0.0f, 1.0f, 0.0}, -circleRad));
                }
            ),
            graphics::Skybox(
                DataStore::insert<graphics::Texture>(
                    new graphics::TextureCubemap(
                        {
                            {"resources/skyboxes/1/right.png"},
                            {"resources/skyboxes/1/left.png"},
                            {"resources/skyboxes/1/top.png"},
                            {"resources/skyboxes/1/bottom.png"},
                            {"resources/skyboxes/1/front.png"},
                            {"resources/skyboxes/1/back.png"}
                        }
                    )
                )
            ),
            std::vector<graphics::Node>{}
        );

        graphics::loadNode(sceneP->nodes, Source("resources/models/WoodBox/WoodBox.gltf"));
        sceneP->nodes.back().transform = math::Transform({0.0f, -0.3f, 0.0f}, {}, {3.0f, 0.3f, 3.0f});
        graphics::loadNode(sceneP->nodes, Source("resources/models/GreenToyDinosaur/GreenToyDinosaur.gltf"));
        sceneP->nodes.back().transform = math::Transform({}, {}, {0.3f, 0.3f, 0.3f});
        //graphics::loadNode(sceneP->nodes, Source("resources/models/Lantern/Lantern.gltf"));
        //sceneP->nodes.back().transform = math::Transform({0.0f, 0.7f, 0.0f}, {}, {0.007f, 0.007f, 0.007f});
        //graphics::loadNode(sceneP->nodes, Source("resources/models/Bullet/Bullet.gltf"));
        //sceneP->nodes.back().transform = math::Transform({0.0f, 0.5f, 0.0f}, {}, {0.005f, 0.005f, 0.005f});

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