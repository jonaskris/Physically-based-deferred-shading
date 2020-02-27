
Table of Contents
=================
   * [What and why](#What-and-why)
     * [Physically based shading](#physically-based-shading)
     * [Deferred shading](#deferred-shading)
   * [Cloning](#cloning)
   * [Building](#building)
   * [Testing](#testing)
   * [Usage](#usage)
   * [<del>Features</del>](#features)
   * [<del>Renders</del>](#renders)
   * [Dependencies](#dependencies)

## What and why
### Physically based shading
Physically based shading is a method of shading that seeks to render lighting in a realistic manner. More specifically, PBR specifies what light gets refracted, gets reflected, and in what direction.

In physically based shading, how much light is refracted or reflected is described by two components; Roughness and metalness. These components are described using textures just like with a normal color texture.

When light is refracted it enters the material itself. Some of the light is absorbed and converted to heat, while some escapes again in a seemingly random direction. The color that escapes is the color of the material itself. For example, grass will refract green light. The light that is refracted of a material is called the diffuse component.

When light is reflected it doesent get absorbed into the material. The light reflects off the material right away, and so the color of reflected light is the color of the light source. For example, an object lit by a red light will also reflect red light.
The light that is reflected of a material is called the specular component.

The roughness component describes the amount of microscopic surface unevenness, and affects the clarity of reflections. A low roughness means the surface is smooth like a mirror, a high roughness leaves the reflection looking blurry and unclear.

The metalness component describes how much metal particles a material consists of. Because individual metal particles reflect incoming light like a mirror, a higher metalness will increase a materials reflective property. A low metalness describes a dielectric, the opposite of a metal, which results in a bigger refractive property.

These components can be described as uniform values where the same value is applied to the whole object being drawn. If textures are used instead of uniform values, details like surface imperfections can be highlighted, which respond well to different light-camera angles.

### Deferred shading
Deferred shading is a shading technique where lighting is deferred(delayed) until the very end of the rendering pipeline. With this technique, rendering is divided into two stages; the geometry stage, and the lighting stage.

During the geometry stage; position, normal, albedo, roughness, metalness and other components of objects are rendered into separate textures in a geometry buffer.

Lighting calculations are deferred to the second stage, where the textures in the geometry buffer are combined to produce the final image.

---

Using traditional forward shading, the entire graphics pipeline is executed per drawn object before drawing the next object.
When an object is drawn, lighting is immediately calculated even on pixels that might end up
being overdrawn by other objects drawn afterwards. With forward shading, a lot of lighting
calculations which are very expensive to calculate dont even end up in the final image.
The reason why with forward shading, expensive lighting calculations are overdrawn, is because
overdrawing is decided during the depth-test stage of the graphics pipeline. With forward shading, depth testing is done after lighting calculations.

With deferred shading, depth testing is done only while writing to this geometry buffer, BEFORE any expensive lighting calculations are performed.
After the geometry stage has filled the geometry buffer, a lighting shader is used in the lighting stage to combine all the textures into one final image.
Deferred shading has an initial cost associated with it because of the introduction of multiple textures in the geometry buffer, resulting in a lot more data needing to be processed. Lighting is also calculated per pixel of the final visible image, instead of per vertex of the geometry.

In return for this big inital cost, the costs of performing lighting calculations are shifted toward being related to the screen resolution, instead of the scene complexity. In addition, deferred shading simplifies the rendering pipeline somewhat by dividing rendering into multiple stages that each have their own isolated responsibilities.

When looking at the highly simplified big O notation for lighting calculations using forward and deferred shading, we can see that forward shading is proportional to the fragment count of the geometry, while deferred shading is proportional to the screen resolution, and therefore stays constant no matter how complex the geometry of the scene is.

`O([number of lights] * ([visible fragments] + [overdrawn fragments]))`

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

## Usage
### Initialization
Initialization is done through the Renderer class, in which the window title, window dimensions and shaders are supplied.

    // Initialization
            // Create Renderer
            Renderer::initialize(
                // Window
                "Physically based deferred shading", 1000, 1000,
                // Shaders
                {
                    {"resources/Shaders/Geometry.vert", Shader::Type::VERTEX}, 
                    {"resources/Shaders/Geometry.frag", Shader::Type::FRAGMENT}
                },
                {
                    {"resources/Shaders/Lighting.vert", Shader::Type::VERTEX}, 
                    {"resources/Shaders/Lighting.frag", Shader::Type::FRAGMENT}
                },
                {
                    {"resources/Shaders/Skybox.vert", Shader::Type::VERTEX}, 
                    {"resources/Shaders/Skybox.frag", Shader::Type::FRAGMENT}
                }
            );

### Resources
Resources can be generated in code (Mesh), or stored (Images) in the resources directory which is symbolically linked to build directory on building.

![/resources/3d-Grafikk.png](RenderData hierarchy)
RenderData hierarchy based on the GLTF format.

Meshes and other referenceable objects in the RenderData hierarchy except Images supply an unsigned int identifier on initialization. Referenceable objects are stored and fetched using the RenderData class.

To generate meshes, classes in Core/Math/Geometry are used which return an unsigned int identifier of the mesh.

#### Examples
Generating meshes:

    // Meshes
    unsigned int icosphere = Icosphere::generate(4);
    unsigned int cubeCubemapped = Cube::generate(true); // True: cubemapped

Loading images:

    // Images
    std::array<Image, 6> skyboxImages =
    {
        Image("resources/images/skybox/left.tga"),  // Left
        Image("resources/images/skybox/right.tga"), // Right
        Image("resources/images/skybox/back.tga"),  // Back
        Image("resources/images/skybox/front.tga"), // Front
        Image("resources/images/skybox/up.tga"),    // Up
        Image("resources/images/skybox/down.tga")   // Down
    };

Creating textures:

    // Cubemap textures
    std::array<unsigned int, 3> rubberTextures
    {
        graphics::RenderData::insert<graphics::TextureCubemap,graphics::Texture>( new graphics::TextureCubema(rubberImages[0])),
        graphics::RenderData::insert<graphics::TextureCubemap,graphics::Texture>( new graphics::TextureCubema(rubberImages[1], GL_RED) ),
        graphics::RenderData::insert<graphics::TextureCubemap,graphics::Texture>( new graphics::TextureCubema(rubberImages[2], GL_RED) )
    };

    unsigned int skyboxTexture = graphics::RenderData::insert<graphics::TextureCubemap,graphics::Texture>( 
        new graphics::TextureCubemap(skyboxImages[0], skyboxImage[1], skyboxImages[2], skyboxImages[3], skyboxImages[4],skyboxImages[5]) 
    );

Creating nodes:

    


## ~~Features~~
## ~~Renders~~
## Dependencies
 - [GLAD](https://github.com/Dav1dde/glad)
 - [GLFW](https://github.com/glfw/glfw)
 - [STB_IMAGE](https://github.com/nothings/stb)
 - [Googletest](https://github.com/google/googletest)

## Special thanks
Special thanks to FreePBR.com for being the projects provider of PBR materials and textures.