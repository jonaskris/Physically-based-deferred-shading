#pragma once

#include <cmath>
#include <cstdint>
#include <map>
#include <vector>
#include <utility>
#include <Vertex.h>
#include <Mesh.h>

namespace Icosphere
{
    namespace
    {
        template <typename VertexType>
        struct Workspace
        {
            static_assert(std::is_same<CubemappedVertex, VertexType>::value, "Icosphere generation is only defined for CubemappedVertex VertexType!");

            std::map<uint64_t, uint32_t> middlePointCache;

            std::vector<VertexType> vertices;
            std::vector<uint32_t> indices;

	        // Creates new vertex and returns index of new point between p1 and p2. (Indices index)
	        uint32_t getMiddlePoint(std::vector<VertexType>& newVertices, std::vector<uint32_t>& newIndices, const uint32_t p1, const uint32_t p2)
            {
	            bool firstIsSmaller = p1 < p2;
	            uint64_t smallerIndex = firstIsSmaller ? p1 : p2;
	            uint64_t biggerIndex = firstIsSmaller ? p2 : p1;
	            uint64_t key = (smallerIndex << 32) + biggerIndex;

	            std::map<uint64_t, uint32_t>::iterator it;
	            if ((it = middlePointCache.find(key)) != middlePointCache.end())
	            {
	        	    return it->second;
	            }

	            math::vec3 vp1 = newVertices[p1].position;
	            math::vec3 vp2 = newVertices[p2].position;

                if constexpr(std::is_same<CubemappedVertex, VertexType>::value)
                {
	                CubemappedVertex midpoint = CubemappedVertex(
                        {((vp1 + vp2) / 2.0f).normalize()}
                    );

                    newVertices.push_back(midpoint);
                }

	            middlePointCache[key] = newVertices.size() - 1;

            	return newVertices.size() - 1;
            }

            void generateBase()
            {
                float t = (1.0f + sqrt(5.0f)) / 2.0f;

                // Vertices/Normals
                vertices.reserve(12);
	            vertices.push_back( VertexType({ math::vec3{-1.0f, t, 0.0f}.normalize() }) );
	            vertices.push_back( VertexType({ math::vec3{ 1.0f, t, 0.0f}.normalize() }) );
	            vertices.push_back( VertexType({ math::vec3{-1.0f,-t, 0.0f}.normalize() }) );
	            vertices.push_back( VertexType({ math::vec3{ 1.0f,-t, 0.0f}.normalize() }) );

	            vertices.push_back( VertexType({ math::vec3{0.0f,-1.0f, t}.normalize() }) );
	            vertices.push_back( VertexType({ math::vec3{0.0f, 1.0f, t}.normalize() }) );
	            vertices.push_back( VertexType({ math::vec3{0.0f,-1.0f,-t}.normalize() }) );
	            vertices.push_back( VertexType({ math::vec3{0.0f, 1.0f,-t}.normalize() }) );

                vertices.push_back( VertexType({ math::vec3{ t, 0.0f,-1.0f}.normalize() }) );
	            vertices.push_back( VertexType({ math::vec3{ t, 0.0f, 1.0f}.normalize() }) );
	            vertices.push_back( VertexType({ math::vec3{-t, 0.0f,-1.0f}.normalize() }) );
	            vertices.push_back( VertexType({ math::vec3{-t, 0.0f, 1.0f}.normalize() }) );

                // Indices
                indices.reserve(60);
	            indices.push_back(0); indices.push_back(11); indices.push_back(5);
	            indices.push_back(0); indices.push_back(5);  indices.push_back(1);
	            indices.push_back(0); indices.push_back(1);  indices.push_back(7);
	            indices.push_back(0); indices.push_back(7);  indices.push_back(10);
	            indices.push_back(0); indices.push_back(10); indices.push_back(11);

                indices.push_back(1);  indices.push_back(5);  indices.push_back(9);
	            indices.push_back(5);  indices.push_back(11); indices.push_back(4);
	            indices.push_back(11); indices.push_back(10); indices.push_back(2);
	            indices.push_back(10); indices.push_back(7);  indices.push_back(6);
                indices.push_back(7);  indices.push_back(1);  indices.push_back(8);

                indices.push_back(3); indices.push_back(9); indices.push_back(4);
                indices.push_back(3); indices.push_back(4); indices.push_back(2);
	            indices.push_back(3); indices.push_back(2); indices.push_back(6);
	            indices.push_back(3); indices.push_back(6); indices.push_back(8);
	            indices.push_back(3); indices.push_back(8); indices.push_back(9);

                indices.push_back(4); indices.push_back(9); indices.push_back(5);
	            indices.push_back(2); indices.push_back(4); indices.push_back(11);
	            indices.push_back(6); indices.push_back(2); indices.push_back(10);
	            indices.push_back(8); indices.push_back(6); indices.push_back(7);
	            indices.push_back(9); indices.push_back(8); indices.push_back(1);
            }

            void subdivide(size_t subdivisions)
            {
                if(subdivisions == 0)
                    return;

                
                for (size_t i = 0; i < subdivisions; i++)
	            {
                    std::vector<uint32_t> subdividedIndices;

	            	for (size_t j = 0; j < indices.size() / 3; j++) // For every face
	            	{
	            		// Add 3 new vertices
	            		uint32_t a = getMiddlePoint(vertices, subdividedIndices, indices[j * 3 + 0], indices[j * 3 + 1]);
	            		uint32_t b = getMiddlePoint(vertices, subdividedIndices, indices[j * 3 + 1], indices[j * 3 + 2]);
	            		uint32_t c = getMiddlePoint(vertices, subdividedIndices, indices[j * 3 + 2], indices[j * 3 + 0]);
                        
                        // Add 12 new indices
	            		subdividedIndices.push_back(indices[j * 3 + 0]); subdividedIndices.push_back(a); subdividedIndices.push_back(c);
	            		subdividedIndices.push_back(indices[j * 3 + 1]); subdividedIndices.push_back(b); subdividedIndices.push_back(a);
	            		subdividedIndices.push_back(indices[j * 3 + 2]); subdividedIndices.push_back(c); subdividedIndices.push_back(b);
	            		subdividedIndices.push_back(a); subdividedIndices.push_back(b); subdividedIndices.push_back(c);
	            	}
                    indices = subdividedIndices;
	            }

                //vertices = subdividedVertices;

                middlePointCache.clear();
            }
        };
    }

    template <typename VertexType>
    Mesh<VertexType>* generate(size_t subdivisions)
    {
        Workspace<VertexType> workspace;
        workspace.generateBase();
        workspace.subdivide(subdivisions);

        return new Mesh<VertexType>(workspace.vertices, workspace.indices);
    }
}