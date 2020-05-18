#pragma once

#include <ProgramRequirement.h>
#include <DataStore.h>
#include <DataIdentifier.h>

namespace graphics
{
    class Program;

    namespace ProgramStore
    {
        namespace
        {
            DataIdentifier<Program> geometryProgram;
            DataIdentifier<Program> lightingProgram;
            DataIdentifier<Program> skyboxProgram;
            DataIdentifier<Program> irradianceMapProgram;
            DataIdentifier<Program> prefilterMapProgram;
            DataIdentifier<Program> brdfLUTProgram;
        }
    
        void setGeometryProgram(Program* program);
        void setLightingProgram(Program* program);
        void setSkyboxProgram(Program* program);
        void setIrradianceMapProgram(Program* program);
        void setPrefilterMapProgram(Program* program);
        void setBrdfLUTProgram(Program* program);
        
        DataIdentifier<Program> getGeometryProgram();
        DataIdentifier<Program> getLightingProgram();
        DataIdentifier<Program> getSkyboxProgram();
        DataIdentifier<Program> getIrradianceMapProgram();
        DataIdentifier<Program> getPrefilterMapProgram();
        DataIdentifier<Program> getBrdfLUTProgram();
    }
}