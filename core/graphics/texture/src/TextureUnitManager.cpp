#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <TextureUnitManager.h>

namespace TextureUnitManager
{
    // Activates texture unit, marks it as used and returns its id.
    // Returns -1 if there are no available texture units.
    int requestTextureUnit()
    {
        for(size_t i = 0; i < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS; i++)
            if(!textureUnits[i])
            {
                glActiveTexture(GL_TEXTURE0 + i);
                textureUnits[i] = true;
                return i;
            }
        return -1;
    }

    // Create a context.
    void pushContext()
    {
        size_t minIndexUnused;
        for(size_t i = 0; i < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS; i++)
            if(!textureUnits[i])
            {
                minIndexUnused = i;
                break;
            }
        contexts.push_back(minIndexUnused);
    }
    
    // Texture units that were marked as used in the context, are marked as unused.
    void popContext()
    {
        for(size_t i = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS; i--;)
            if(i >= contexts.back())
                textureUnits[i] = false;
            else
                break;
        contexts.pop_back();
    }
}