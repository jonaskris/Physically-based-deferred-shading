#pragma once

#include <Mesh.h>
#include <Material.h>
#include <Program.h>
#include <DataIdentifier.h>
#include <DataStore.h>

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