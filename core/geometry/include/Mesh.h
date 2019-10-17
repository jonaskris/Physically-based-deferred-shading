#include <vector>
#include <glad/glad.h>
#include <Vec3.h>

namespace geometry
{
    struct Vertex
    {
        math::vec3 position;
        math::vec3 normal;
    };

    class Mesh
    {
    private:
        std::vector<Vertex> vertices;
        std::vector<size_t> indices;

        GLuint VAO;
        GLuint VBO;
        GLuint IBO;

    public:
        void initialize();
        void draw();
    };
}