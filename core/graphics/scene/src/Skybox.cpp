#include <Skybox.h>

#include <glad/glad.h>

#include <DataStore.h>
#include <Program.h>
#include <ProgramStore.h>
#include <Mat4.h>
#include <Defines.h>
#include <Icosphere.h>
#include <Plane.h>

#include <TextureUnitManager.h>

const uint IRRADIANCE_MAP_DIMENSIONS =  32;
const uint PREFILTER_MAP_DIMENSIONS = 256;
const uint PREFILTER_MAP_MIP_LEVELS = 5;
const uint BRDFLUT_DIMENSIONS = 512;

namespace graphics
{
    DataIdentifier<Mesh> Skybox::mesh = DataIdentifier<Mesh>(0);
    DataIdentifier<Texture> Skybox::brdfLUT = DataIdentifier<Texture>(0);
    
    void Skybox::generateIrradianceMap()
    {
        // Preparation
        Texture* environmentMapTexture = DataStore::get<Texture>(environmentMap);

        math::Mat4 captureProjection = math::Mat4::perspective(math::Degrees(90.0f), 1.0f, 0.1f, 10.0f);
        std::vector<math::Mat4> captureViews
        {
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3( 1.0f,  0.0f,  0.0f), math::Vec3(0.0f, -1.0f, 0.0f)), // +x
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3(-1.0f,  0.0f,  0.0f), math::Vec3(0.0f, -1.0f, 0.0f)), // -x
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3( 0.0f,  1.0f,  0.0f), math::Vec3(0.0f, 0.0f, 1.0f)),  // +y
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3( 0.0f, -1.0f,  0.0f), math::Vec3(0.0f, 0.0f, -1.0f)), // -y
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3( 0.0f,  0.0f,  1.0f), math::Vec3(0.0f, -1.0f, 0.0f)), // +z
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3( 0.0f,  0.0f, -1.0f), math::Vec3(0.0f, -1.0f, 0.0f))  // -z
        };
        Mesh* captureMesh = DataStore::get<Mesh>(mesh);
        Program* captureProgram = DataStore::get<Program>(ProgramStore::getProgram(defines::ProgramType::IRRADIANCEMAP));

        // Setup framebuffer
        GLuint FBO;
        GLuint RBO;
        glGenFramebuffers(1, &FBO);
        glGenRenderbuffers(1, &RBO);

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, IRRADIANCE_MAP_DIMENSIONS, IRRADIANCE_MAP_DIMENSIONS);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);

        // Save viewport dimensions so they can be set back to original state afterwards
        GLint viewportDimensions[4];
        glGetIntegerv(GL_VIEWPORT, viewportDimensions);

        // Create irradiance texture
        GLuint textureId;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        for(size_t i = 0; i < 6; i++)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, IRRADIANCE_MAP_DIMENSIONS, IRRADIANCE_MAP_DIMENSIONS, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);            

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);  

        Texture* irradianceMapTexture = new Texture(defines::SamplerType::SAMPLERCUBE, textureId, IRRADIANCE_MAP_DIMENSIONS, IRRADIANCE_MAP_DIMENSIONS);

        // Bind capture program and set uniforms
        TextureUnitManager::pushContext();
        captureProgram->enable();
        captureProgram->setCubemap("environmentMap", environmentMapTexture->getTextureId());
        captureProgram->setUniformMat4f("projection", captureProjection);

        // Use FBO to render textures
        glViewport(0, 0, IRRADIANCE_MAP_DIMENSIONS, IRRADIANCE_MAP_DIMENSIONS);
        
        glDisable(GL_CULL_FACE);
        for(size_t i = 0; i < 6; i++)
        {
            captureProgram->setUniformMat4f("view", captureViews[i]);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradianceMapTexture->getTextureId(), 0);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            captureMesh->draw();
        }
        glEnable(GL_CULL_FACE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(viewportDimensions[0], viewportDimensions[1], viewportDimensions[2], viewportDimensions[3]);

        glDeleteFramebuffers(1, &FBO);
        TextureUnitManager::popContext();

        irradianceMap = DataStore::insert<Texture>(irradianceMapTexture);    
    }

    void Skybox::generatePrefilterMap()
    {
        // Preparation
        Texture* environmentMapTexture = DataStore::get<Texture>(environmentMap);

        math::Mat4 captureProjection = math::Mat4::perspective(math::Degrees(90.0f), 1.0f, 0.1f, 10.0f);
        std::vector<math::Mat4> captureViews
        {
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3( 1.0f,  0.0f,  0.0f), math::Vec3(0.0f, -1.0f, 0.0f)), // +x
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3(-1.0f,  0.0f,  0.0f), math::Vec3(0.0f, -1.0f, 0.0f)), // -x
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3( 0.0f,  1.0f,  0.0f), math::Vec3(0.0f, 0.0f, 1.0f)),  // +y
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3( 0.0f, -1.0f,  0.0f), math::Vec3(0.0f, 0.0f, -1.0f)), // -y
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3( 0.0f,  0.0f,  1.0f), math::Vec3(0.0f, -1.0f, 0.0f)), // +z
            math::Mat4::view(math::Vec3(0.0f, 0.0f, 0.0f), math::Vec3( 0.0f,  0.0f, -1.0f), math::Vec3(0.0f, -1.0f, 0.0f))  // -z
        };
        Mesh* captureMesh = DataStore::get<Mesh>(mesh);
        Program* captureProgram = DataStore::get<Program>(ProgramStore::getProgram(defines::ProgramType::PREFILTERMAP));

        // Setup framebuffer
        GLuint FBO;
        GLuint RBO;
        glGenFramebuffers(1, &FBO);
        glGenRenderbuffers(1, &RBO);

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, PREFILTER_MAP_DIMENSIONS, PREFILTER_MAP_DIMENSIONS);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);

        // Save viewport dimensions so they can be set back to original state afterwards
        GLint viewportDimensions[4];
        glGetIntegerv(GL_VIEWPORT, viewportDimensions);

        // Create prefilter texture
        GLuint textureId;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        for(size_t i = 0; i < 6; i++)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, PREFILTER_MAP_DIMENSIONS, PREFILTER_MAP_DIMENSIONS, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);            

        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);  

        Texture* prefilterTexture = new Texture(defines::SamplerType::SAMPLERCUBE, textureId, IRRADIANCE_MAP_DIMENSIONS, IRRADIANCE_MAP_DIMENSIONS);
        
        // Bind capture program and set uniforms
        TextureUnitManager::pushContext();
        captureProgram->enable();
        captureProgram->setCubemap("environmentMap", environmentMapTexture->getTextureId());
        captureProgram->setUniformMat4f("projection", captureProjection);
        captureProgram->setUniform1ui("resolution", environmentMapTexture->getWidth()); // Width == height for cubemap

        // Use FBO to render textures
        glDisable(GL_CULL_FACE);
        for(size_t mip = 0; mip < PREFILTER_MAP_MIP_LEVELS; mip++)
        {
            size_t mipDimensions = PREFILTER_MAP_DIMENSIONS * std::pow(0.5, mip);

            // Resize renderbuffer
            glBindRenderbuffer(GL_RENDERBUFFER, RBO);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipDimensions, mipDimensions);
            glViewport(0, 0, mipDimensions, mipDimensions);

            float roughness = (float)mip / (float)(PREFILTER_MAP_MIP_LEVELS - 1);
            captureProgram->setUniform1f("roughness", roughness);

            for(size_t i = 0; i < 6; i++)
            {
                captureProgram->setUniformMat4f("view", captureViews[i]);

                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilterTexture->getTextureId(), mip);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                captureMesh->draw();
            }
        }
        glEnable(GL_CULL_FACE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(viewportDimensions[0], viewportDimensions[1], viewportDimensions[2], viewportDimensions[3]);

        glDeleteFramebuffers(1, &FBO);
        TextureUnitManager::popContext();

        prefilterMap = DataStore::insert<Texture>(prefilterTexture);        
    }

    void Skybox::generateBRDFLUT()
    {
        static DataIdentifier<Mesh> planeMesh;
        if(!planeMesh)
            planeMesh = DataStore::insert<Mesh>(new Mesh(math::geometry::Plane::generate()));

        Mesh* captureMesh = DataStore::get<Mesh>(planeMesh);
        Program* captureProgram = DataStore::get<Program>(ProgramStore::getProgram(defines::ProgramType::BRDFLUT));

        // Setup framebuffer
        GLuint FBO;
        GLuint RBO;
        glGenFramebuffers(1, &FBO);
        glGenRenderbuffers(1, &RBO);

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, BRDFLUT_DIMENSIONS, BRDFLUT_DIMENSIONS);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);

        // Save viewport dimensions so they can be set back to originalPREFILTER_MAP_DIMENSIONS state afterwards
        GLint viewportDimensions[4];
        glGetIntegerv(GL_VIEWPORT, viewportDimensions);

        // Create BRDFLUT texture
        GLuint textureId;

        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_2D, textureId);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, BRDFLUT_DIMENSIONS, BRDFLUT_DIMENSIONS, 0, GL_RG, GL_FLOAT, nullptr);

        glBindTexture(GL_TEXTURE_2D, 0);  

        Texture* brdfLUTTexture = new Texture(defines::SamplerType::SAMPLER2D, textureId, BRDFLUT_DIMENSIONS, BRDFLUT_DIMENSIONS);

        // Bind capture program and set uniforms
        captureProgram->enable();
        captureProgram->setUniformMat4f("projection", math::Mat4::orthographic(-0.5f, 0.5f, -0.5f, 0.5f, -0.5f, 0.5f));

        // Use FBO to render texture

        glViewport(0, 0, BRDFLUT_DIMENSIONS, BRDFLUT_DIMENSIONS);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUTTexture->getTextureId(), 0);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        captureMesh->draw();

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(viewportDimensions[0], viewportDimensions[1], viewportDimensions[2], viewportDimensions[3]);

        glDeleteFramebuffers(1, &FBO);

        brdfLUT = DataStore::insert<Texture>(brdfLUTTexture);        
    }

    Skybox::Skybox(DataIdentifier<Texture> environmentMap) : environmentMap(environmentMap) 
    {
        if(!mesh)
            mesh = DataStore::insert<Mesh>(new Mesh(math::geometry::Icosphere::generate(1)));

        generateIrradianceMap();
        generatePrefilterMap();
        if(!brdfLUT)
            generateBRDFLUT();
    }

    DataIdentifier<Mesh> Skybox::getMesh() const { return mesh; }
    DataIdentifier<Texture> Skybox::getEnvironmentMap() const { return environmentMap; }
    DataIdentifier<Texture> Skybox::getIrradianceMap() const { return irradianceMap; }
    DataIdentifier<Texture> Skybox::getPrefilterMap() const { return prefilterMap; }
    DataIdentifier<Texture> Skybox::getBRDFLUT() const { return brdfLUT; }
    
}