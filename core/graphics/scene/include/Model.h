#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Node.h>
#include <Mesh.h>
#include <Material.h>

class Model : public Node
{
private:
    Material* material;
    MeshBase* mesh;

public:
    Model(Material* material, MeshBase* mesh) : material(material), mesh(mesh) {};

    void setUniforms(GLuint programId) override
    {
        if(material)
            material->set(programId);
    }

    void draw() const override
    {
        mesh->draw();
    }
};