#pragma once

#include <utility>

#include <Program.h>
#include <ProgramRequirement.h>

#include <DataStore.h>
#include <DataIdentifier.h>

namespace graphics
{
    class ProgramGenerator
    {
    private:
        std::vector<std::pair<ProgramRequirement, DataIdentifier<Program>>> programs;

    protected:
        void insertProgram(const ProgramRequirement& programRequirement, DataIdentifier<Program> program);

    public:
        DataIdentifier<Program> getProgram(const ProgramRequirement& programRequirement);
        virtual DataIdentifier<Program> generate(const ProgramRequirement& programRequirement) = 0;
    };
}