#pragma once

#include <Mesh.h>
#include <Texture.h>
#include <Icosphere.h>

#include <DataIdentifier.h>
#include <DataStore.h>

namespace graphics
{
    class Skybox
    {
    private:
        static DataIdentifier<Mesh> mesh;
        static DataIdentifier<Texture> brdfLUT;
        DataIdentifier<Texture> environmentMap;
        DataIdentifier<Texture> irradianceMap;
        DataIdentifier<Texture> prefilterMap;    
            

        void generateIrradianceMap();
        void generatePrefilterMap();
        void generateBRDFLUT();

    public:
        Skybox(DataIdentifier<Texture> environmentMap);

        DataIdentifier<Mesh> getMesh() const;
        DataIdentifier<Texture> getEnvironmentMap() const;
        DataIdentifier<Texture> getIrradianceMap() const;
        DataIdentifier<Texture> getPrefilterMap() const;
        DataIdentifier<Texture> getBRDFLUT() const;
    };
}