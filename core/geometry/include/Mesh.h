#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <Vec3.h>
#include <Vertex.h>

namespace geometry
{
    class MeshBase
    {
    protected:
        virtual void initialize() = 0;

    public:
        virtual void draw() const = 0;
    };

    template <typename VertexType>
    class Mesh : public MeshBase
    {
    protected:
        std::vector<VertexType> vertices;
        std::vector<size_t> indices;

        GLuint VAO;
        GLuint VBO;
        GLuint IBO;

        void initialize() override
        {
            // VBO
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            // IBO
            glGenBuffers(1, &IBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(size_t) * indices.size(), &indices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);  

            // VAO
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

            VertexType::describeVAOLayout();

            glBindVertexArray(0);
        }

        Mesh() {};

    public:
        void draw() const override
        {
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid*)(0));
            glBindVertexArray(0);
        }

        template <typename U>
        friend std::ostream& operator<<(std::ostream& out, const Mesh<U>& mesh);
    };

    template <typename VertexType>
    std::ostream& operator<<(std::ostream& out, const Mesh<VertexType>& mesh)
    {
        out << "Mesh: Vertices size: " << mesh.vertices.size() << ", Indices size: " << mesh.indices.size();
        return out;
    }
}