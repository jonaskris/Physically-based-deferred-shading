#include <vector>
#include <Model.h>
#include <Mesh.h>
#include <Uniform.h>
#include <glad/glad.h>  

Model::Model(const std::vector<Uniform*>& uniforms, const std::vector<geometry::MeshBase*>& meshes) : uniforms(uniforms), meshes(meshes) {};

void Model::setUniforms(GLuint programId) const
{
    for(const Uniform* const uniform : uniforms )
        uniform->set(programId);
}

void Model::drawMeshes() const
{
    for(const geometry::MeshBase* const mesh : meshes)
        mesh->draw();
}