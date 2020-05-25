
Table of Contents
=================
   * [Showcase](#Showcase)
   * [Features](#features)
   * [What and why](#What-and-why)
     * [Physically based shading](#Physically-based-shading)
     * [Deferred shading](#Deferred-shading)
   * [Cloning](#Cloning)
   * [Building](#Building)
   * [Testing](#Testing)
   * [Dependencies](#Dependencies)

## Showcase
![](/Showcase.gif)

Left to right: Wooden cube, green toy dinosaur, lantern, bullet.

High resolution video in repository (Showcase.mov).

## Features
* Physically based and deferred shading
* Model loading with ASSIMP
* Image based lighting
* Basic sort-based drawcall bucketing
* Self-written linear algebra library

## What and why
### Physically based shading
Physically based shading is a method of shading that seeks to render lighting in a realistic manner.

In physically based shading, how much light is refracted or reflected is described by two components; Roughness and metalness.

The roughness component describes the amount of microscopic surface unevenness, and affects the clarity of reflections. A low roughness means the surface is smooth like a mirror, a high roughness leaves the reflection looking blurry and unclear.

The metalness component describes how much metal particles a material consists of. Because individual metal particles reflect incoming light like a mirror, a higher metalness will increase a materials reflective property.

### Deferred shading
Deferred shading is a shading technique where lighting is deferred(delayed) until the very end of the rendering pipeline. With this technique, rendering is divided into two stages; the geometry stage, and the lighting stage.

During the geometry stage; position, normal, albedo, roughness, metalness and other attributes of objects are rendered into separate textures in a geometry buffer.

Lighting calculations are deferred to the second stage, where the textures in the geometry buffer are combined to produce the final image.

## Cloning
The project uses googletest and assimp as submodules. To pull submodules with the project, add the argument --recurse-submodules.

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

## Dependencies
 - [GLAD](https://github.com/Dav1dde/glad)
 - [GLFW](https://github.com/glfw/glfw)
 - [STB_IMAGE](https://github.com/nothings/stb)
 - [Googletest](https://github.com/google/googletest)
 - [Assimp](https://github.com/assimp/assimp)