#include <ProgramStore.h>

#include <Program.h>

#include <DataStore.h>
#include <DataIdentifier.h>

namespace graphics
{
    namespace ProgramStore
    {
        void setGeometryProgram(Program* program) { geometryProgram = DataStore::insert<Program>(program); }
        void setLightingProgram(Program* program) { lightingProgram = DataStore::insert<Program>(program); }
        void setSkyboxProgram(Program* program) { skyboxProgram = DataStore::insert<Program>(program); }
        void setIrradianceMapProgram(Program* program) { irradianceMapProgram = DataStore::insert<Program>(program); }
        void setPrefilterMapProgram(Program* program) { prefilterMapProgram = DataStore::insert<Program>(program); }
        void setBrdfLUTProgram(Program* program) { brdfLUTProgram = DataStore::insert<Program>(program); }

        DataIdentifier<Program> getGeometryProgram() { return geometryProgram; }
        DataIdentifier<Program> getLightingProgram() { return lightingProgram; }
        DataIdentifier<Program> getSkyboxProgram() { return skyboxProgram; }
        DataIdentifier<Program> getIrradianceMapProgram() { return irradianceMapProgram; }
        DataIdentifier<Program> getPrefilterMapProgram() { return prefilterMapProgram; }
        DataIdentifier<Program> getBrdfLUTProgram() { return brdfLUTProgram; }
    }
}