#pragma once

#include <set>

#include <Mesh.h>
#include <Material.h>
#include <ProgramStore.h>

#include <DataIdentifier.h>
#include <DataStore.h>
#include <ProgramRequirement.h>

namespace graphics
{
    struct DrawUnit
    {
        DataIdentifier<Mesh> mesh;
        DataIdentifier<Material> material;
        DataIdentifier<Program> program;

        DrawUnit(DataIdentifier<Mesh> mesh, DataIdentifier<Material> material, DataIdentifier<Program> program) : mesh(mesh), material(material), program(program) {}
    };
}