#include <Material.h>

#include <Uniform.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Material::set(GLuint programId)
{
    albedo->set(programId);
}