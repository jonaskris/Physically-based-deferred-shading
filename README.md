# Physically based deferred shading
### Physically based shading
Physically based shading is technique in 3D graphics that seeks to model lighting in a realistic manner.

### Deferred shading
Deferred shading is a lighting optimization where rendering is done in two passes; Geometry, and Lighting.
During the geometry stage; color, albedo, position, normals and other properties are rendered into their separate textures in a geometry buffer.
Lighting calculations are delayed, or "deferred" to the second pass, where the textures from the first pass are combined into the final image.
The main advantage of deferred shading is that expensive lighting calculations only are performed on the pixels that will be visible in the final image. The alternative to deferred shading is forward rendering, where lighting is calculated with rendering of the geometry. Forward rendering will calculate lighting even for geometry that wont be visible in the final image.

## Building
The project is compiled using CMake.
Run script below from the main directory:

    mkdir build 
    cd build 
    cmake .. 
    make	
## ~~Usage~~
## ~~Features~~
## ~~Renders~~

## Dependencies

 - [GLAD](https://github.com/Dav1dde/glad)
 - [GLFW](https://github.com/glfw/glfw)
 

