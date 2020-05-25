#include <Renderer.h>

#include <vector>
#include <iostream>
#include <algorithm>

#include <glad/glad.h>

#include <Window.h>
#include <Program.h>
#include <DataStore.h>
#include <TextureUnitManager.h>
#include <RenderQueue.h>
#include <Scene.h>
#include <Defines.h>
#include <ProgramStore.h>
#include <Geometry.h>
#include <Mesh.h>
#include <Plane.h>
#include <Camera.h>
#include <Input.h>

namespace graphics
{
    Renderer* Renderer::instance = nullptr;

    Renderer::Renderer(const std::string& windowTitle, size_t windowWidth, size_t windowHeight)
        : window(new Window(windowTitle, windowWidth, windowHeight)),
        framebuffer(new graphics::Framebuffer(windowWidth, windowHeight))
    {
        // Default perspective
        fov = math::Degrees(45.0f);
        aspectratio = (float)windowWidth / (float)windowHeight;
        nearP = 0.01f;
        farP = 20.0f;
        setPerspective();

        // Default orthographic
        left = -0.5f;
        right = 0.5f;
        bottom = -0.5f;
        top = 0.5f;
        nearO = -0.5f;
        farO = 0.5f;
        setOrthographic();

        // Plane mesh
        planeMesh = DataStore::insert<Mesh>(new Mesh(math::geometry::Plane::generate()));

        glEnable(GL_DEPTH_TEST);
        glFrontFace(GL_CCW);
        glEnable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
        glPointSize(3.0f);
        glClearColor(1.0f, 0.7f, 0.3f, 1.0f);
    };

    Renderer::~Renderer()
    {
        delete window;
        delete framebuffer;
        projection = {};
    };

    Renderer* Renderer::init(const std::string& windowTitle, size_t windowWidth, size_t windowHeight)
    {
        instance = new Renderer(windowTitle, windowWidth, windowHeight);
        return instance;
    }
            
    Renderer* Renderer::getInstance()
    {
        return instance;
    }

    bool Renderer::windowClosed() { return window->closed(); }

    void Renderer::render(DataIdentifier<Scene> scene, RenderMode rendermode)
    {
// Geometry
        // Bind framebuffer
        framebuffer->bind();

        // Clear framebuffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Scene* sceneP = DataStore::get<Scene>(scene);
        sceneP->renderQueue.reset();
        sceneP->renderQueue.process(sceneP->nodes);

        uint16_t currentProgramId;
        Program* currentProgram;

        uint16_t currentMaterialId;
        Material* currentMaterial;

        uint16_t currentMeshId;
        Mesh* currentMesh;

        const std::vector<uint64_t>& drawKeys = sceneP->renderQueue.getDrawKeys();

        for(size_t i = 0; i < drawKeys.size(); i++)
        {
            uint16_t programId, materialId, meshId, transform;
            DrawKey::read(drawKeys[i], programId, materialId, meshId, transform);

            if(programId != currentProgramId || i == 0)
            {
                if(i != 0)
                    currentProgram->disable();

                currentProgramId = programId;
                currentProgram = DataStore::get<Program>(DataIdentifier<Program>(currentProgramId));

                currentProgram->enable();

                currentProgram->setUniformMat4f("projection", projection);
                currentProgram->setUniformMat4f("view", sceneP->camera->getViewMatrix());
            }

            currentProgram->setUniformMat4f("model", sceneP->renderQueue.getTransforms()[transform]);

            if(materialId != currentMaterialId || i == 0)
            {
                currentMaterialId = materialId;
                currentMaterial = DataStore::get<Material>(DataIdentifier<Material>(currentMaterialId));
            }

            if(meshId != currentMeshId || i == 0)
            {
                currentMeshId = meshId;
                currentMesh = DataStore::get<Mesh>(DataIdentifier<Mesh>(currentMeshId));
            }

            bool doubleSided;
            currentMaterial->set(*currentProgram, doubleSided);

            if(doubleSided)
                glDisable(GL_CULL_FACE);

            currentMesh->draw();

            if(doubleSided)
                glEnable(GL_CULL_FACE);
        }        
        currentProgram->disable();

        // Unbind framebuffer
        framebuffer->unbind();

// Lighting
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Enable lighting pass program
        currentProgram = DataStore::get<Program>(ProgramStore::getProgram(defines::ProgramType::LIGHTING));
        currentProgramId = currentProgram->getId();
        currentProgram->enable();

        //lightPosition = math::toVec3(math::Mat4::rotate(math::Degrees(1.0f), {0.0f, 1.0f, 0.0f}) * math::toVec4(lightPosition, 1.0f));
        //Uniform::setVec3(programId, "lightPosition", lightPosition);

        // Push texture unit context
        TextureUnitManager::pushContext();

        // Bind framebuffer textures
        currentProgram->setTexture2D("g_position", framebuffer->position->getId());
        currentProgram->setTexture2D("g_normal", framebuffer->normal->getId());
        currentProgram->setTexture2D("g_albedo", framebuffer->albedo->getId());
        currentProgram->setTexture2D("g_metallness_roughness", framebuffer->metallness_roughness->getId());
        currentProgram->setCubemap("irradianceMap", DataStore::get<Texture>(sceneP->skybox.getIrradianceMap())->getTextureId());
        currentProgram->setCubemap("prefilterMap", DataStore::get<Texture>(sceneP->skybox.getPrefilterMap())->getTextureId());
        currentProgram->setTexture2D("brdfLUT", DataStore::get<Texture>(sceneP->skybox.getBRDFLUT())->getTextureId());

        // Set uniforms
        currentProgram->setUniformMat4f("projection", orthographic);
        currentProgram->setUniformVec3f("viewPosition", sceneP->camera->getPosition());
        
        currentProgram->setUniform1ui("renderMode", (uint32_t)rendermode);
        //lightPosition = math::toVec3(math::Mat4::rotate(math::Degrees(1.0f), {0.0f, 1.0f, 0.0f}) * math::toVec4(lightPosition, 1.0f));
        currentProgram->setUniformVec3f("lightPosition", lightPosition);
        currentProgram->setUniformVec3f("lightColor", lightColor);

        // Draw screen-wide quad
        DataStore::get<Mesh>(planeMesh)->draw();
        
        // Pop texture unit context
        TextureUnitManager::popContext();

        // Disable lighting pass program
        currentProgram->disable();

// Skybox
        // Set depth func to less than or equal
        glDepthFunc(GL_LEQUAL);

        // Set face culling to front
        glCullFace(GL_FRONT);

        // Blit (copy) framebuffer depth to main buffer
        glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer->getId());
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, window->getWidth(), window->getHeight(), 0, 0, window->getWidth(), window->getHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);

            // Enable skybox pass program
            currentProgram = DataStore::get<Program>(ProgramStore::getProgram(defines::ProgramType::SKYBOX));
            currentProgramId = currentProgram->getId();
            currentProgram->enable();

            // Set uniforms
            currentProgram->setUniformMat4f("projection", projection);
            currentProgram->setUniformMat4f("view", sceneP->camera->getViewMatrix().removeTranslation());
            currentProgram->setUniformMat4f("model", math::Mat4::identity());

                // Push texture unit context
                TextureUnitManager::pushContext();
                
                // Draw skybox geometry
                Texture* skyboxTexture = DataStore::get<Texture>(sceneP->skybox.getEnvironmentMap() );
                currentProgram->setCubemap("skybox", skyboxTexture->getTextureId());
                currentMesh = DataStore::get<Mesh>(sceneP->skybox.getMesh());
                currentMesh->draw();
                // Pop texture unit context
                TextureUnitManager::popContext();

            // Disable skybox pass program
            currentProgram->disable();

        // Set face culling to back (Default)
        glCullFace(GL_BACK);

        // Set depth func to less than (Default)
        glDepthFunc(GL_LESS);

        // Update window 
        window->update();
        
        // Update timing
        double timeThisFrame = glfwGetTime();
        deltatime = timeThisFrame - timeLastFrame;
        fps = (size_t)(1.0 / deltatime);
        timeLastFrame = timeThisFrame;
    }

    size_t Renderer::getFPS()
    {
        return fps;
    }

    double Renderer::getDeltatime()
    {
        return deltatime;
    }
    
    void Renderer::setPerspective(std::optional<math::Radians> newFov, std::optional<float> newAspectratio, std::optional<float> newNear, std::optional<float> newFar)
    {
        if(newFov)
            fov = newFov.value();
        if(newAspectratio)
            aspectratio = newAspectratio.value();
        if(newNear)
            nearP = newNear.value();
        if(newFar)
            farP = newFar.value();

        projection = math::Mat4::perspective(fov, aspectratio, nearP, farP);
    }

    // Updates orthographic matrix arguments if argument is not 0 and updates the matrix
    void Renderer::setOrthographic(std::optional<float> newLeft, std::optional<float> newRight, std::optional<float> newBottom, std::optional<float> newTop, std::optional<float> newNear, std::optional<float> newFar)
    {
        if(newLeft)
            left = newLeft.value();
        if(newRight)
            right = newRight.value();
        if(newBottom)
            bottom = newBottom.value();
        if(newTop)
            top = newTop.value();
        if(newNear)
            nearO = newNear.value();
        if(newFar)
            farO = newFar.value();

        orthographic = math::Mat4::orthographic(left, right, bottom, top, nearO, farO);
    }
}