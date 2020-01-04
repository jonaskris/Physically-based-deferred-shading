#include <Model.h>

#include <glad/glad.h>

#include <Mesh.h>
#include <Material.h>
#include <RenderData.h>
#include <Uniform.h>
#include <RenderData.h>

namespace graphics
{
    
    Model::Model(unsigned int mesh, unsigned int material, math::Transform transform, std::vector<unsigned int> childrenNodes) : Node(childrenNodes, transform), mesh(mesh), material(material) {}

    void Model::process(GLuint programId, math::Mat4 parentTransform)
    {
        // Set transform
        parentTransform = transform.toMatrix() * parentTransform;
        Uniform::setMat4(programId, "model", parentTransform);

        // Set material
        if(material)
        {
            graphics::Material* m = graphics::RenderData::get<graphics::Material>(material);
            m->set(programId);
        } else
        {
            // Set default material?
            std::cout << "Couldent find material!" << std::endl;
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
        }
    }
}