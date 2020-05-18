#pragma once

#include <cmath>
#include <cstdint>
#include <map>
#include <vector>
#include <utility>

#include <Geometry.h>
#include <VertexAttribute.h>

namespace math::geometry
{
    namespace Icosphere
    {
        namespace
        {
            struct Workspace
            {
                std::map<uint64_t, uint32_t> middlePointCache;

                std::vector<float> vertices;
                std::vector<uint32_t> indices;

                uint32_t getMiddlePoint(std::vector<float>& newVertices, std::vector<uint32_t>& newIndices, const uint32_t p1, const uint32_t p2);
                void generateBase();
                void subdivide(size_t subdivisions);
            };
        }

        Geometry generate(size_t subdivisions);
    }
}