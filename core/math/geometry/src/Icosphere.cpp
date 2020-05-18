#include <Icosphere.h>

#include <Vec3.h>

namespace math::geometry::Icosphere
{
// Creates new vertex and returns index of new point between p1 and p2. (Indices index)
    uint32_t Workspace::getMiddlePoint(std::vector<float>& newVertices, std::vector<uint32_t>& newIndices, const uint32_t p1, const uint32_t p2)
    {
        bool firstIsSmaller = p1 < p2;
        uint64_t smallerIndex = firstIsSmaller ? p1 : p2;
        uint64_t biggerIndex = firstIsSmaller ? p2 : p1;
        uint64_t key = (smallerIndex << 32) + biggerIndex;

    	std::map<uint64_t, uint32_t>::iterator it;
    	if ((it = middlePointCache.find(key)) != middlePointCache.end())
    	    return it->second;

    	math::Vec3 vp1 = {newVertices[p1 * 6], newVertices[p1 * 6 + 1], newVertices[p1 * 6 + 2]};
    	math::Vec3 vp2 = {newVertices[p2 * 6], newVertices[p2 * 6 + 1], newVertices[p2 * 6 + 2]};

        math::Vec3 midpoint = ((vp1 + vp2) / 2.0f).normalize() / 2.0f; // Both position and normal

        newVertices.insert(newVertices.end(), midpoint.elements, midpoint.elements + 3);
        newVertices.insert(newVertices.end(), midpoint.elements, midpoint.elements + 3);

    	middlePointCache[key] = (newVertices.size() / 6) - 1;

        return (newVertices.size() / 6) - 1;
    }

    void Workspace::generateBase()
    {
        float t = (1.0f + sqrt(5.0f)) / 2.0f;
        float s = 1.0f;
        float l = sqrt(t * t + s * s);
        t /= l;
        s /= l;
        t /= 2.0f;
        s /= 2.0f;

        vertices = 
        {// | Position |   Normal  |
            -s, t, 0.0f,-s, t, 0.0f, 
             s, t, 0.0f, s, t, 0.0f, 
            -s,-t, 0.0f,-s,-t, 0.0f, 
             s,-t, 0.0f, s,-t, 0.0f, 
             0.0f,-s, t, 0.0f,-s, t, 
             0.0f, s, t, 0.0f, s, t, 
             0.0f,-s,-t, 0.0f,-s,-t, 
             0.0f, s,-t, 0.0f, s,-t, 
             t, 0.0f,-s, t, 0.0f,-s, 
             t, 0.0f, s, t, 0.0f, s, 
            -t, 0.0f,-s,-t, 0.0f,-s, 
            -t, 0.0f, s,-t, 0.0f, s
        };

        indices = 
        {
            0, 11, 5,
            0, 5, 1,
            0, 1, 7,
            0, 7, 10,
            0, 10, 11,

            1, 5, 9,
            5, 11, 4,
            11, 10, 2,
            10, 7, 6,
            7, 1, 8,

            3, 9, 4,
            3, 4, 2,
            3, 2, 6,
            3, 6, 8,
            3, 8, 9,

            4, 9, 5,
            2, 4, 11,
            6, 2, 10,
            8, 6, 7,
            9, 8, 1
        };
    }

    void Workspace::subdivide(size_t subdivisions)
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

        middlePointCache.clear();
    }

    Geometry generate(size_t subdivisions)
    {
        Workspace workspace;
        workspace.generateBase();
        workspace.subdivide(subdivisions);

        std::vector<VertexAttribute> vertexAttributes
        {
            // Position
            VertexAttribute{defines::VertexAttribute::POSITION, 0, defines::NumeralType::VEC3, GL_FLOAT,  false, 6 * sizeof(float), (const void*)(0)},

            // Normal
            VertexAttribute{defines::VertexAttribute::NORMAL, 1, defines::NumeralType::VEC3, GL_FLOAT,  true, 6 * sizeof(float), (const void*)(3 * sizeof(float))}
        };

        return Geometry(workspace.vertices, vertexAttributes, workspace.indices, GL_TRIANGLES);
    }
}