#pragma once

#include <glad/glad.h>

#include <vector>

#include <Utils.h>
#include <Vec3.h>
#include <Mat4.h>
#include <Transform.h>

#include <Input.h>
#include <Node.h>

namespace graphics
{
    class Camera : public Node
    {
    private:
        math::Mat4 view;

    public:
        Camera(math::Transform transform, std::vector<unsigned int> childrenNodes);

        void process(GLuint programId, math::Mat4 parentTransform = {}) override;
        math::Mat4 getView() const;
    };

    class FirstPersonCamera : public Camera, public Input::Mouse::DeltaPositionListener, public Input::Keyboard::KeyListener
    {
    private:
        math::Radians yaw, pitch;

    public:
        FirstPersonCamera(const math::Vec3& position, math::Radians yaw, math::Radians pitch, std::vector<unsigned int> childrenNodes);

        void deltaPositionCallback(double deltatime, const std::vector<Input::Mouse::PositionEvent>& positionEvents) override;
        void keyCallback(double deltatime, const std::vector<Input::Keyboard::KeyEvent>& keyEvents) override;
    };
}