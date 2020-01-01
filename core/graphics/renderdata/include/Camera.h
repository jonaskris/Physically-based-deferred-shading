#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Utils.h>
#include <Vec3.h>
#include <Mat4.h>
#include <Node.h>
#include <Input.h>

namespace graphics
{
    class Camera : public Node
    {
    private:
        math::Mat4 view;

    protected:
        math::Vec3 lookFrom;
        math::Vec3 lookAt;
        math::Vec3 up;

    public:
        Camera(const math::Vec3& lookFrom, const math::Vec3& lookAt, const math::Vec3& up);
        Camera(const math::Vec3& lookFrom, math::Radians yaw, math::Radians pitch);

        void process(GLuint programId) override;
    };

    class FirstPersonCamera : public Camera, public Input::Mouse::DeltaPositionListener, public Input::Keyboard::KeyListener
    {
    private:
        math::Radians yaw, pitch;
        math::Vec3 forward;

    public:
        FirstPersonCamera(const math::Vec3& lookFrom, const math::Vec3& up, math::Radians yaw, math::Radians pitch);

        void deltaPositionCallback(double deltatime, const std::vector<Input::Mouse::PositionEvent>& positionEvents) override;
        void keyCallback(double deltatime, const std::vector<Input::Keyboard::KeyEvent>& keyEvents) override;
    };
}