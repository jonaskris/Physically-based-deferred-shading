#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Material.h>

#include <Uniform.h>

void Material::set(GLuint programId)
{
    albedo->set(programId);
}