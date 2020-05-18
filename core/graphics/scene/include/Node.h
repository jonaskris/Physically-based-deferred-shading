#pragma once

#include <vector>
#include <cstdint>

#include <Transform.h>
#include <DataIdentifier.h>
#include <DrawUnit.h>

namespace graphics
{
    struct Node
    {
        std::vector<DrawUnit> drawUnits; // Units of mesh, material and program
        math::Transform transform; // Transform relative to parent
        
        std::vector<Node> children;

        Node() {}
        Node(const std::vector<DrawUnit>& drawUnits, const math::Transform& transform = {}, const std::vector<Node>& children = {}) : drawUnits(drawUnits), transform(transform), children(children) {}
    };
}