#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Vec2.h>
#include <Vec3.h>
#include <Mat4.h>
#include <Uniform.h>
#include <Node.h>
#include <Input.h>

class Camera : public Node
{
private:
    UniformMat4f view;

protected:
    math::vec3 lookFrom;
    math::vec3 lookAt;
    math::vec3 up;

public:
    Camera(const math::vec3& lookFrom, const math::vec3& lookAt, const math::vec3& up);
    
    void setUniforms(GLuint programId) override;
    void draw() const override {};
};

class FirstPersonCamera : public Camera, public MousePositionListener, public KeyboardListener
{
private:
    float yaw, pitch;
    math::vec3 forward;

public:
    FirstPersonCamera(const math::vec3& lookFrom, const math::vec3& up, float yaw, float pitch);

    void positionCallback(math::vec2 position) override;
    void keyCallback(const KeyEvent keyEvent) override;
};