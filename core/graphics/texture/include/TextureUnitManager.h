#pragma once

#include <vector>

#include <glad/glad.h>

namespace TextureUnitManager
{
    static bool textureUnits[GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS] = {};
    static std::vector<size_t> contexts;

    /*
        Activates texture unit, marks it as used and returns its id.
        Returns -1 if there are no available texture units.
    */
    GLuint requestTextureUnit();

    /* 
        Create a context in which requested texture units are assigned.
    */
    void pushContext();
    
    /* 
        Pop context. Marks texture units that were used in the context as
        unused.
    */
    void popContext();
}