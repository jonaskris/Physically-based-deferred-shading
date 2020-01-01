#include <Model.h>

#include <glad/glad.h>

#include <Mesh.h>
#include <Material.h>
#include <RenderData.h>

namespace graphics
{
    Model::Model(unsigned int mesh, unsigned int material) : mesh(mesh), material(material) {}

    void Model::process(GLuint programId)
    {
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
    }
}