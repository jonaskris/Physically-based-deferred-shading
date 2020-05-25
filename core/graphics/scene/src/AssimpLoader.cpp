#include <AssimpLoader.h>

#include <algorithm>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/pbrmaterial.h>

#include <VertexAttribute.h>
#include <Geometry.h>
#include <DataIdentifier.h>
#include <DataStore.h>
#include <DrawUnit.h>
#include <Image.h>
#include <Program.h>
#include <Defines.h>
#include <ProgramStore.h>

namespace graphics
{
    /*
        Loads assimp model as node and inserts into specified vector of nodes.
    */
    void loadNode(std::vector<Node>& nodes, const Source& source)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(source.getFullSource(), aiProcess_Triangulate | aiProcess_GenUVCoords | aiProcess_GenNormals | aiProcess_CalcTangentSpace);

        // Check for errors
        if( !scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
        {
            std::cout << "Assimp error: " << importer.GetErrorString( ) << std::endl;
            return;
        }

        nodes.emplace_back(); // Top level node

        // Process ASSIMP's root node recursively
        processNode(nodes.back(), scene->mRootNode, scene, source);
    }

    /*
        Process individual nodes.
    */
    void processNode(Node& currentNode, aiNode* node, const aiScene* scene, const Source& source)
    {
        // Process each mesh located at the current node
        for (size_t i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* assimpMesh = scene->mMeshes[node->mMeshes[i]];

            size_t numUVChannels;
            DataIdentifier<Mesh> mesh = processMesh(assimpMesh, scene, numUVChannels);
            DataIdentifier<Material> material;

            if(assimpMesh->mMaterialIndex >= 0)
            {
                aiMaterial* aimaterial = scene->mMaterials[assimpMesh->mMaterialIndex];
                material = processMaterial(aimaterial, scene, source, numUVChannels);
            }

            // In future, non-pbr models will be assigned a different program.
            DataIdentifier<Program> program = ProgramStore::getProgram(defines::ProgramType::GEOMETRY);
            
            currentNode.drawUnits.emplace_back(mesh, material, program);
        }

        // Recursively process each of the children nodes
        for (size_t i = 0; i < node->mNumChildren; i++)
        {
            currentNode.children.emplace_back();
            processNode(currentNode.children.back(), node->mChildren[i], scene, source);
        }
    }

    DataIdentifier<Mesh> processMesh(aiMesh* mesh, const aiScene* scene, size_t& numUVChannels)
    {
    // Data to fill
        std::vector<uint32_t> indices;
        std::vector<float> vertices;
        std::vector<math::geometry::VertexAttribute> vertexAttributes;

    // Describe vertex attributes
        size_t offset = 0;

        // Position
        vertexAttributes.emplace_back( math::geometry::VertexAttribute{defines::VertexAttribute::POSITION, 0, defines::NumeralType::VEC3, GL_FLOAT, GL_FALSE, 0, (const void*)(offset * sizeof(float))} );
        offset += 3;

        // Normal
        vertexAttributes.emplace_back( math::geometry::VertexAttribute{defines::VertexAttribute::NORMAL, 0, defines::NumeralType::VEC3, GL_FLOAT, GL_TRUE, 0, (const void*)(offset * sizeof(float))} );
        offset += 3;

        // Tangents and bitangents
        if(mesh->HasTangentsAndBitangents())
        {
            vertexAttributes.emplace_back( math::geometry::VertexAttribute{defines::VertexAttribute::TANGENT, 0, defines::NumeralType::VEC3, GL_FLOAT, GL_TRUE, 0, (const void*)(offset * sizeof(float))} );
            offset += 3;
            
            vertexAttributes.emplace_back( math::geometry::VertexAttribute{defines::VertexAttribute::BITANGENT, 0, defines::NumeralType::VEC3, GL_FLOAT, GL_TRUE, 0, (const void*)(offset * sizeof(float))} );
            offset += 3;
        }
        
        // Texture coordinates
        numUVChannels = mesh->GetNumUVChannels();
        for(size_t i = 0; i < numUVChannels; i++)
        {
            vertexAttributes.emplace_back( math::geometry::VertexAttribute{defines::VertexAttribute::UV, (GLuint)i, (defines::NumeralType)mesh->mNumUVComponents[i], GL_FLOAT, GL_FALSE, 0, (const void*)(offset * sizeof(float))} );
            offset += mesh->mNumUVComponents[i];
        }
        
        // Set stride for each vertex attribute
        for(size_t i = 0; i < vertexAttributes.size(); i++)
            vertexAttributes[i].stride = offset * sizeof(float);

    // Set vertices vector
        for(size_t i = 0; i < mesh->mNumVertices; i++)
        {
            // Position
            vertices.push_back(mesh->mVertices[i].x);
            vertices.push_back(mesh->mVertices[i].y);
            vertices.push_back(mesh->mVertices[i].z);

            // Normal
            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);

            // Tangents and bitangents
            if(mesh->HasTangentsAndBitangents())
            {
                vertices.push_back(mesh->mTangents[i].x);
                vertices.push_back(mesh->mTangents[i].y);
                vertices.push_back(mesh->mTangents[i].z);

                vertices.push_back(mesh->mBitangents[i].x);
                vertices.push_back(mesh->mBitangents[i].y);
                vertices.push_back(mesh->mBitangents[i].z);
            }

            // Texture coordinates
            for(size_t j = 0; j < numUVChannels; j++)
                for(size_t k = 0; k < mesh->mNumUVComponents[j]; k++)
                    if(k == 1) // Invert second UV as OpenGL address image data upside down from most image formats
                        vertices.push_back(-mesh->mTextureCoords[j][i][k]);
                    else
                        vertices.push_back(mesh->mTextureCoords[j][i][k]);
        }

        // Set indices vector
        for (size_t i = 0; i < mesh->mNumFaces; i++)
            // Get indices of face
            for (size_t j = 0; j < 3; j++)
                indices.push_back(mesh->mFaces[i].mIndices[j]);

        return DataStore::insert<Mesh>( new Mesh(math::geometry::Geometry(vertices, vertexAttributes, indices, GL_TRIANGLES)) );    
    }    

    DataIdentifier<Material> processMaterial(aiMaterial* assimpMaterial, const aiScene* scene, const Source& source, size_t uvCount)
    {
        Material::MaterialAttribute materialAttributeAlbedo;
        Material::MaterialAttribute materialAttributeNormal;
        Material::MaterialAttribute materialAttributeMetallnessRoughness;

        // 1. Albedo texture
        auto albedoTexture = loadMaterialTexture(assimpMaterial, defines::MaterialAttribute::ALBEDO, source, uvCount);
        if(albedoTexture)
            materialAttributeAlbedo = Material::MaterialAttribute{albedoTexture, {}, 3};
        else
        {
            aiColor3D color;
            if(assimpMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
            {
                materialAttributeAlbedo = Material::MaterialAttribute{DataIdentifier<Texture>(0), {color.r, color.g, color.b, 0.0f}, 3};
            } else
                throw std::runtime_error("Failed to load material as it doesent have an albedo texture or color!");
        }

        // 2. Normal texture
        auto normalTexture = loadMaterialTexture(assimpMaterial, defines::MaterialAttribute::NORMAL, source, uvCount);
        if(normalTexture)
            materialAttributeNormal = Material::MaterialAttribute{normalTexture, {}, 3};
        else
            materialAttributeNormal = Material::MaterialAttribute{DataIdentifier<Texture>(0), {0.0f, 0.0f, 1.0f, 0.0}, 3};

        // 3. Metalness/Roughness texture
        auto metalRoughnessTexture = loadMaterialTexture(assimpMaterial, defines::MaterialAttribute::METALLNESS_ROUGHNESS, source, uvCount);
        if(metalRoughnessTexture)
            materialAttributeMetallnessRoughness = Material::MaterialAttribute{metalRoughnessTexture, {}, 2};
        else
        {
            aiColor3D colorMetallness;
            if(assimpMaterial->Get(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLIC_FACTOR, colorMetallness) != AI_SUCCESS)
                colorMetallness.r = 0.5f;

            aiColor3D colorRoughness;
            if(assimpMaterial->Get(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_ROUGHNESS_FACTOR, colorRoughness) != AI_SUCCESS)
                colorRoughness.r = 0.5f;

            materialAttributeMetallnessRoughness = Material::MaterialAttribute{DataIdentifier<Texture>(0), {colorMetallness.r, colorRoughness.r, 0.0f, 0.0f}, 2};
        }

        int twoSided;
        assimpMaterial->Get(AI_MATKEY_TWOSIDED, twoSided);

        return DataStore::insert<Material>(new Material(materialAttributeAlbedo, materialAttributeNormal, materialAttributeMetallnessRoughness, (bool)twoSided));
    }

    DataIdentifier<Texture> loadMaterialTexture(aiMaterial* assimpMaterial, defines::MaterialAttribute type, const Source& source, size_t uvCount)
    {
        aiString imageName;
        int uvIndex;
        if(type == defines::MaterialAttribute::METALLNESS_ROUGHNESS)
        {
            if(assimpMaterial->GetTexture(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLICROUGHNESS_TEXTURE, &imageName) != AI_SUCCESS)
                return DataIdentifier<Texture>(0);
        } else
        {
            aiTextureType textureType;
            switch(type)
            {
                case defines::MaterialAttribute::ALBEDO: textureType = aiTextureType_DIFFUSE; break;
                case defines::MaterialAttribute::NORMAL: textureType = aiTextureType_NORMALS; break;
            }

            if(assimpMaterial->GetTexture(textureType, 0, &imageName) != AI_SUCCESS)
                return DataIdentifier<Texture>(0);

            // Assign uv index
            if(uvCount == 1 || assimpMaterial->Get(AI_MATKEY_UVWSRC(textureType, 0), uvIndex) != AI_SUCCESS)
                uvIndex = 0;
        }

        Source imageSource(source.getDirectory() + imageName.C_Str());

        return DataIdentifier<Texture>(DataStore::insert<Texture>( (Texture*)(new Texture2D(imageSource)) ));
    }
}