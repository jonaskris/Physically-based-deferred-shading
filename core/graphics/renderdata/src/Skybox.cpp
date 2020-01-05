#include <Skybox.h>

#include <glad/glad.h>

#include <Model.h>
#include <Transform.h>
#include <Uniform.h>
#include <RenderData.h>
#include <Material.h>
#include <Mesh.h>

namespace graphics
{

    Skybox::Skybox(unsigned int mesh, unsigned int material) : Model(mesh, material, {}, {}) {}

    void Skybox::process(GLuint programId, math::Mat4 parentTransform)
    {
// Set transform
        parentTransform = transform.toMatrix() * parentTransform;
        Uniform::setMat4(programId, "model", parentTransform);

        // Set material
        if(material)
        {
            graphics::Material* m = graphics::RenderData::get<graphics::Material>(material);
            m->set(programId);
        }

        // Draw mesh
        if(mesh)
        {
            graphics::Mesh* m = graphics::RenderData::get<graphics::Mesh>(mesh);

            if(m)
                m->draw();
        }

        // Process childrenNodes
        for(unsigned int n : childrenNodes)
        {
            graphics::Node* node = graphics::RenderData::get<graphics::Model>(n);
            if(node)
                node->process(programId, parentTransform);
        }    }
}