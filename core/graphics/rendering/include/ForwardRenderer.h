#include <Renderer.h>
#include <Program.h>

namespace graphics
{
    class ForwardRenderer : public Renderer
    {
    public:
        ForwardRenderer(Program* program);

        void render() override;
    };
}