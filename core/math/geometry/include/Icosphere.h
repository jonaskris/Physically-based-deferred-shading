#pragma once

#include <cmath>
#include <cstdint>
#include <map>
#include <Mesh.h>
#include <Vertex.h>
#include <utility>

class Icosphere : public Mesh<CubemappedVertex>
{
private:
    std::map<uint64_t, size_t> middlePointCache;

	// Creates new vertex and returns index of new point between p1 and p2. (Indices index)
	size_t getMiddlePoint(std::pair<std::vector<CubemappedVertex>, std::vector<size_t>>& verticesIndicesPair, const size_t& p1, const size_t& p2)
    {
	    bool firstIsSmaller = p1 < p2;
	    uint64_t smallerIndex = firstIsSmaller ? p1 : p2;
	    uint64_t biggerIndex = firstIsSmaller ? p2 : p1;
	    uint64_t key = (smallerIndex << 32) + biggerIndex;
	
	    std::map<uint64_t, size_t>::iterator it;
	    if ((it = middlePointCache.find(key)) != middlePointCache.end())
	    {
		    return it->second;
	    }

	    CubemappedVertex vp1 = verticesIndicesPair.first[p1];
	    CubemappedVertex vp2 = verticesIndicesPair.first[p2];
		
	    CubemappedVertex midpoint = CubemappedVertex(
            math::vec3
			{
		        (vp1.position.elements[0] + vp2.position.elements[0]) / 2.0f, 
		        (vp1.position.elements[1] + vp2.position.elements[1]) / 2.0f, 
		        (vp1.position.elements[2] + vp2.position.elements[2]) / 2.0f
			}.normalize()
        );

	    verticesIndicesPair.first.push_back(midpoint);
	    middlePointCache[key] = verticesIndicesPair.first.size() - 1;

    	return verticesIndicesPair.first.size() - 1;
    }
    void generate(size_t subdivision)
    {
        std::pair<std::vector<CubemappedVertex>, std::vector<size_t>> base;

        // Generate base
        float t = (1.0f + sqrt(5.0f)) / 2.0f;
        // Vertices/Normals
        base.first.reserve(12);
	    base.first.push_back(math::vec3{-1.0f, t, 0.0f}.normalize());
	    base.first.push_back(math::vec3{ 1.0f, t, 0.0f}.normalize());
	    base.first.push_back(math::vec3{-1.0f,-t, 0.0f}.normalize());
	    base.first.push_back(math::vec3{ 1.0f,-t, 0.0f}.normalize());

	    base.first.push_back(math::vec3{0.0f,-1.0f, t}.normalize());
	    base.first.push_back(math::vec3{0.0f, 1.0f, t}.normalize());
	    base.first.push_back(math::vec3{0.0f,-1.0f,-t}.normalize());
	    base.first.push_back(math::vec3{0.0f, 1.0f,-t}.normalize());
	
        base.first.push_back(math::vec3{ t, 0.0f,-1.0f}.normalize());
	    base.first.push_back(math::vec3{ t, 0.0f, 1.0f}.normalize());
	    base.first.push_back(math::vec3{-t, 0.0f,-1.0f}.normalize());
	    base.first.push_back(math::vec3{-t, 0.0f, 1.0f}.normalize());

        // Indices
        base.second.reserve(60);
	    base.second.push_back(0); base.second.push_back(11); base.second.push_back(5);
	    base.second.push_back(0); base.second.push_back(5); base.second.push_back(1);
	    base.second.push_back(0); base.second.push_back(1); base.second.push_back(7);
	    base.second.push_back(0); base.second.push_back(7); base.second.push_back(10);
	    base.second.push_back(0); base.second.push_back(10); base.second.push_back(11);
	
        base.second.push_back(1); base.second.push_back(5); base.second.push_back(9);
	    base.second.push_back(5); base.second.push_back(11); base.second.push_back(4);
	    base.second.push_back(11); base.second.push_back(10); base.second.push_back(2);
	    base.second.push_back(10); base.second.push_back(7); base.second.push_back(6);
        base.second.push_back(7); base.second.push_back(1); base.second.push_back(8);
    
        base.second.push_back(3); base.second.push_back(9); base.second.push_back(4);
        base.second.push_back(3); base.second.push_back(4); base.second.push_back(2);
	    base.second.push_back(3); base.second.push_back(2); base.second.push_back(6);
	    base.second.push_back(3); base.second.push_back(6); base.second.push_back(8);
	    base.second.push_back(3); base.second.push_back(8); base.second.push_back(9);
	
        base.second.push_back(4); base.second.push_back(9); base.second.push_back(5);
	    base.second.push_back(2); base.second.push_back(4); base.second.push_back(11);
	    base.second.push_back(6); base.second.push_back(2); base.second.push_back(10);
	    base.second.push_back(8); base.second.push_back(6); base.second.push_back(7);
	    base.second.push_back(9); base.second.push_back(8); base.second.push_back(1);

        if(subdivision != 0)
        {
            // Subdivide
            std::pair<std::vector<CubemappedVertex>, std::vector<size_t>> old = base;
            std::pair<std::vector<CubemappedVertex>, std::vector<size_t>> subdivided;
            subdivided.first = old.first;

            for (size_t i = 0; i < subdivision; i++)
	        {
	        	std::vector<size_t> newIndices;
	        	for (size_t j = 0; j < old.second.size() / 3; j++) // For every face
	        	{
	        		// Add 3 new vertices
	        		size_t a = getMiddlePoint(subdivided, old.second[j * 3 + 0], old.second[j * 3 + 1]);
	        		size_t b = getMiddlePoint(subdivided, old.second[j * 3 + 1], old.second[j * 3 + 2]);
	        		size_t c = getMiddlePoint(subdivided, old.second[j * 3 + 2], old.second[j * 3 + 0]);
                    // Add 12 new indices
	        		newIndices.push_back(old.second[j * 3 + 0]); 	newIndices.push_back(a); newIndices.push_back(c);
	        		newIndices.push_back(old.second[j * 3 + 1]); 	newIndices.push_back(b); newIndices.push_back(a);
	        		newIndices.push_back(old.second[j * 3 + 2]); 	newIndices.push_back(c); newIndices.push_back(b);
	        		newIndices.push_back(a); newIndices.push_back(b); newIndices.push_back(c);
	        	}
	        	subdivided.second = newIndices;
	        }

            Mesh<CubemappedVertex>::vertices = subdivided.first;
            Mesh<CubemappedVertex>::indices = subdivided.second;

            middlePointCache.clear();

            return;
        }
        Mesh<CubemappedVertex>::vertices = base.first;
        Mesh<CubemappedVertex>::indices = base.second;
        middlePointCache.clear();
    }
public:
    Icosphere(size_t subdivision)
    {
        generate(subdivision);
        initialize();
    };    
};