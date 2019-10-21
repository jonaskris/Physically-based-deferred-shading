#include <Renderer.h>
#include <Framebuffer.h>

namespace graphics
{
    class DeferredRenderer : public DeferredRenderer
    {
    private:
        Framebuffer* framebuffer;
    public:
        DeferredRenderer(size_t width, size_t height);
        ~DeferredRenderer();

        void render() override;
    };
}