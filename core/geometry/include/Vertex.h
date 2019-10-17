#include <vector>
#include <Vec3.h>
#include <glad/glad.h>

namespace geometry
{
    struct VertexContainerBase 
    {
    public:
        virtual void submitVertices();
    };

    struct Vertex
    {
        math::vec3 position;
        math::vec3 normal;
    };

    template <typename VertexType>
    struct VertexContainer : public VertexContainerBase
    {
    private:
        std::vector<VertexType> vertices;
        std::vector<size_t> indices;

    public:
        void submitVertices() override
        {
            static bool initialized = false;
            static GLuing VAO;
            static GLuint VBO;
            static GLuint IBO;

            if(!initialized)
            {
                initialized = true;

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

                if constexpr (std::is_same<Vertex, VertexType>::value)
                {
                    glEnableVertexAttribArray(0);
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexType), (const GLvoid*)(offsetof(VertexType, VertexType::position)));
                    
                    glEnableVertexAttribArray(1);
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(VertexType), (const GLvoid*)(offsetof(VertexType, VertexType::normal)));
                }        

                glBindVertexArray(0);
            }

            // Draw
            glBindVertexArray(VAO);

            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (GLvoid*)(0));

            glBindVertexArray(0);
        }
    };
}