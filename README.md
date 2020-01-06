
Table of Contents
=================
   * [What and why](#What-and-why)
     * [Physically based shading](#physically-based-shading)
     * [Deferred shading](#deferred-shading)
   * [Cloning](#cloning)
   * [Building](#building)
   * [Testing](#testing)
   * [<del>Usage</del>](#usage)
   * [<del>Features</del>](#features)
   * [<del>Renders</del>](#renders)
   * [Dependencies](#dependencies)

## What and why
### Physically based shading
Physically based shading is a technique in 3D graphics that seeks to model lighting in a realistic manner. To achieve this, properties such as reflection and diffusion are used to describe the geometry to be drawn. 

These properties can be described using single values that are uniformly applied to a geometry, or using texture mapping. Texture mapping can give results such as small dents and imperfections that are only visible when viewed from certain angles.

### Deferred shading
Deferred shading is a lighting optimization where rendering is done in two passes; Geometry, and Lighting.

During the geometry stage; color, albedo, position, normals and other properties of the geometry are rendered into their separate textures in a geometry buffer.

Lighting calculations are delayed, or "deferred" to the second pass, where the textures from the first pass and lighting information are combined into the final image.

---

Lets take a look at how simplified models of forward rendering and deferred shading with minimal optimizations calculate lighting.

Using traditional forward rendering, as much of lighting calculations as possible is first done in the vertex shader, and finally refined in the fragment shader. The set of lighting calculations done in the vertex and fragment shader are in a simplified model, done on every single vertex and fragment of a given mesh, regardless of if the result will be visible in the final image. The reason for this, is that determining what fragments overdraw which, is first done during the depth testing stage of the render pipeline, which comes after the fragment shader (and therefore lighting calculations).

When using deferred shading, depth testing is done for every texture in the geometry buffer before any lighting calculations are done. The costs related to drawing to multiple textures, and the per-pixel nature of deferred shading results in a big "initial cost". The price of this initial cost becomes easier to justify with modern hardware as scene complexity grows in demand. 

When looking at the big O notation (Highly simplified) of both methods, we see that the cost of lighting calculations in traditional forward rendering is proportional to both the number of lights, and the geometric complexity of the scene. The cost of lighting calculations in deferred shading is not proportional to the geometric complexity, but rather the screen resolution.

Forward rendering complexity: 

`O([number of lights] * ([visible fragments] + [overdrawn fragments]))`

Deferred rendering complexity: 

`O([number of lights] * [screen resolution])`


## Cloning
The project uses googletest as a submodule. To pull submodules with the project, add the argument --recurse-submodules.

    git clone --recurse-submodules https://github.com/jonaskris/Physically-based-deferred-shading.git

## Building
The project is compiled using CMake.

Run commands below from the main directory.

    mkdir build 
    cd build 
    cmake .. 
    make	

## Testing
To run tests after building, run the command below from the build directory.

    make tests
## ~~Usage~~
## ~~Features~~
## ~~Renders~~
## Dependencies
 - [GLAD](https://github.com/Dav1dde/glad)
 - [GLFW](https://github.com/glfw/glfw)
 - [STB_IMAGE](https://github.com/nothings/stb)

## Special thanks
Special thanks to FreePBR.com for being the projects provider of PBR materials and textures.