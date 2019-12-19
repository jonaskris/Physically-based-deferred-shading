#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Utils.h>
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
    math::Vec3 lookFrom;
    math::Vec3 lookAt;
    math::Vec3 up;

public:
    Camera(const math::Vec3& lookFrom, const math::Vec3& lookAt, const math::Vec3& up);
    
    void setUniforms(GLuint programId) override;
    void draw() const override {};
};

class FirstPersonCamera : public Camera, public Input::Mouse::DeltaPositionListener, public Input::Keyboard::KeyListener
{
private:
    math::Degrees yaw, pitch;
    math::Vec3 forward;

public:
    FirstPersonCamera(const math::Vec3& lookFrom, const math::Vec3& up, math::Degrees yaw, math::Degrees pitch);

    void deltaPositionCallback(double deltatime, const std::vector<Input::Mouse::PositionEvent>& positionEvents) override;
    void keyCallback(double deltatime, const std::vector<Input::Keyboard::KeyEvent>& keyEvents) override;
};