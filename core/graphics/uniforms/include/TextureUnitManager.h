#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TextureUnitManager
{
    static bool textureUnits[GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS] = {};
    static std::vector<size_t> contexts;

    // Activates texture unit, marks it as used and returns its id.
    // Returns -1 if there are no available texture units.
    int requestTextureUnit();

    // Create a context.
    void pushContext();
    
    // Texture units that were marked as used in the context, are marked as unused.
    void popContext();
}