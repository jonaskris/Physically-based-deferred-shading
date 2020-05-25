#pragma once

#include <map>

#include <Defines.h>
#include <DataIdentifier.h>

namespace graphics
{
    class Program;

    namespace ProgramStore
    {
        namespace
        {
            std::map<defines::ProgramType, DataIdentifier<Program>> programs;
        }
    
        void setProgram(defines::ProgramType programType, Program* program);
        DataIdentifier<Program> getProgram(defines::ProgramType programType);
    }
}