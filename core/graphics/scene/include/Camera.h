#pragma once

#include <Vec3.h>
#include <Mat4.h>
#include <Uniform.h>

class Camera : public UniformMat4f
{
protected:
    math::vec3 lookFrom;
    math::vec3 lookAt;
    math::vec3 up;

public:
    Camera(const math::vec3& lookFrom, const math::vec3& lookAt, const math::vec3& up = math::vec3(0.0f, 0.0f, 1.0f));
    
    virtual void update();
};