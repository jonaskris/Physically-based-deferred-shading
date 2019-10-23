#include <vector>
#include <Uniform.h>
#include <glad/glad.h>

namespace geometry
{
    class MeshBase;
}

class Model
{
private:
    std::vector<Uniform*> uniforms;
    std::vector<geometry::MeshBase*> meshes;

public:
    Model(const std::vector<Uniform*>& uniforms, const std::vector<geometry::MeshBase*>& meshes);

    void setUniforms(GLuint programId) const;
    void drawMeshes() const;
};