#pragma once

#include <ProgramGenerator.h>

#include <Program.h>
#include <ProgramRequirement.h>

#include <DataStore.h>
#include <DataIdentifier.h>

namespace graphics
{
    class GeometryProgramGenerator : public ProgramGenerator
    {
    public:
        DataIdentifier<Program> generate(const ProgramRequirement& programRequirement) override;
    };
}