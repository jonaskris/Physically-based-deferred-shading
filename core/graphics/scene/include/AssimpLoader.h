#pragma once

#include <vector>

#include <Node.h>
#include <DataIdentifier.h>
#include <Mesh.h>
#include <Material.h>
#include <Texture.h>
#include <Source.h>

class aiScene;
class aiNode;
class aiMesh;
class aiMaterial;

namespace graphics
{
    /*
        Loads assimp model as node and inserts into specified vector of nodes.
    */
    void loadNode(std::vector<Node>& nodes, const Source& source);

    void processNode(Node& newNode, aiNode* node, const aiScene* scene, const Source& source);

    DataIdentifier<Mesh> processMesh(aiMesh* mesh, const aiScene* scene, size_t& numUVChannels);

    DataIdentifier<Material> processMaterial(aiMaterial* material, const aiScene* scene, const Source& source, size_t uvCount);
    
    DataIdentifier<Texture> loadMaterialTexture(aiMaterial* material, defines::MaterialAttribute type, const Source& source, size_t uvCount);
}