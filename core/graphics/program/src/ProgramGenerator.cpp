#include <ProgramGenerator.h>

#include <algorithm>

#include <ProgramRequirement.h>

#include <DataStore.h>
#include <DataIdentifier.h>

namespace graphics
{
    void ProgramGenerator::insertProgram(const ProgramRequirement& programRequirement, DataIdentifier<Program> program)
    {
        programs.emplace_back(programRequirement, program);
    }

    DataIdentifier<Program> ProgramGenerator::getProgram(const ProgramRequirement& programRequirement)
    {
        auto it = std::find_if(programs.begin(), programs.end(), 
        [&]( std::pair<ProgramRequirement, DataIdentifier<Program>>& element)
        {
            return element.first == programRequirement;
        });
    
        if(it != programs.end())
            return it->second;
        else
            return DataIdentifier<Program>(0);
    }
}