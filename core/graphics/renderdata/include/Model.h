#pragma once

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.hpp>
#include <assimp/postprocess.hpp>

#include "Mesh.h"

namespace graphics
{
    class Model
    {
    private:
        std::vector<Mesh> meshes;
        std::vector<Texture> textures;
        std::String directory;
        bool hasTextureCoordinates = false;

    public:
        Model(const std::String& path)
        {
            loadModel(path);
        }

    private:
        void loadModel(const std::String& path)
        {
            // Read file via ASSIMP
            Assimp::Importer importer;
            const aiScene *scene = importer.ReadFile( path, aiProcess_Triangulate );

            // Check for errors
            if( !scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) // if is Not Zero
            {
                cout << "ERROR::ASSIMP:: " << importer.GetErrorString( ) << endl;
                return;
            }
            // Retrieve the directory path of the filepath
            this->directory = path.substr( 0, path.find_last_of( '/' ) );

            // Process ASSIMP's root node recursively
            this->processNode( scene->mRootNode, scene );
        }

        void processNode(aiNode* node, const aiScene* scene)
        {
            // Process each mesh located at the current node
            for (size_t i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

                this->meshes.push_back( this->processMesh( mesh, scene ) );
            }

            // Recursively process each of the children nodes
            for (size_t i = 0; i < node->mNumChildren; i++)
                this->processNode( node->mChildren[i], scene );
        }

        Mesh processMesh(aiMesh* mesh, const aiScene* scene)     
        {
            // Data to fill
            //vector<Vertex> vertices;
            //vector<GLuint> indices;
            //vector<Texture> textures;

            

            // Walk through each of the mesh's vertices
            for (size_t i = 0; i < mesh->mNumVertices; i++)
            {
                Vertex vertex;
                glm::vec3 vector; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.

                // Positions
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                vertex.Position = vector;

                // Normals
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;

                // Texture Coordinates
                if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
                {
                    hasTextureCoordinates = true;
                    glm::vec2 vec;
                    
                    // A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
                    // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                    vec.x = mesh->mTextureCoords[0][i].x;
                    vec.y = mesh->mTextureCoords[0][i].y;
                    vertex.TexCoords = vec;
                } else
                {
                    vertex.TexCoords = glm::vec2( 0.0f, 0.0f );
                }

                vertices.push_back( vertex );
            }

            


            // Now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
            for ( GLuint i = 0; i < mesh->mNumFaces; i++ )
            {
                aiFace face = mesh->mFaces[i];
                // Retrieve all indices of the face and store them in the indices vector
                for ( GLuint j = 0; j < face.mNumIndices; j++ )
                {
                    indices.push_back( face.mIndices[j] );
                }
            }

            // Process materials
            if( mesh->mMaterialIndex >= 0 )
            {
                aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
                // We assume a convention for sampler names in the shaders. Each diffuse texture should be named
                // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
                // Same applies to other texture as the following list summarizes:
                // Diffuse: texture_diffuseN
                // Specular: texture_specularN
                // Normal: texture_normalN

                // 1. Diffuse maps
                vector<Texture> diffuseMaps = this->loadMaterialTextures( material, aiTextureType_DIFFUSE, "texture_diffuse" );
                textures.insert( textures.end( ), diffuseMaps.begin( ), diffuseMaps.end( ) );

                // 2. Specular maps
                vector<Texture> specularMaps = this->loadMaterialTextures( material, aiTextureType_SPECULAR, "texture_specular" );
                textures.insert( textures.end( ), specularMaps.begin( ), specularMaps.end( ) );
            }

            // Return a mesh object created from the extracted mesh data
            return Mesh( vertices, indices, textures );
        }    

        vector<Texture> loadMaterialTextures( aiMaterial *mat, aiTextureType type, string typeName )
        {
            
        }   
    };
}