#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vec3.h>
#include <Mat4.h>
#include <Uniform.h>
#include <Node.h>

class Camera : public Node
{
private:
    UniformMat4f view;
    UniformMat4f projection;

public:
    math::vec3 lookFrom;
    math::vec3 lookAt;
    math::vec3 up;

    float fov;
    float aspectratio;
    float near;
    float far;


public:
    Camera(const math::vec3& lookFrom, const math::vec3& lookAt, const math::vec3& up, float fov, float aspectratio, float near, float far);
    
    void setUniforms(GLuint programId) override;
    void draw() const override {};
};