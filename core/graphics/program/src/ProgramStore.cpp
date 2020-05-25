#include <ProgramStore.h>

#include <DataStore.h>

namespace graphics
{
    namespace ProgramStore
    {
        void setProgram(defines::ProgramType programType, Program* program)
        {
            programs[programType] = DataStore::insert<Program>(program);
        }

        DataIdentifier<Program> getProgram(defines::ProgramType programType)
        {
            auto programIt = programs.find(programType);

            if(programIt != programs.end())
                return programIt->second;
            else
                return DataIdentifier<Program>(0);
        }
    }
}