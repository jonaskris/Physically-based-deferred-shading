#pragma once

#include <vector>

#include <Utils.h>
#include <Vec3.h>
#include <Mat4.h>
#include <Transform.h>
#include <functional>

#include <Input.h>

namespace graphics
{
    class Camera
    {
    private:
        math::Mat4 viewMatrix;
        bool viewDirty = true; // True if viewMatrix must be updated from new transform

        math::Transform transform;

        void updateViewMatrix();

    protected:
        Camera() {};

        void setTransform(const math::Transform& transform);

    public:
        math::Mat4 getViewMatrix();
        const math::Transform& getTransform() const;
        math::Vec3 getPosition() const;
    };

    class AnimatedCamera : public Camera, public Input::Time::TimeListener
    {
    private:
        std::function<math::Transform (double)> animationFunc;

    public:
        AnimatedCamera(std::function<math::Transform (double)> animationFunc);

        void timeCallback(const Input::Time::TimeEvent& timeEvent) override;
    };

    class FPSCamera : public Camera, public Input::Mouse::DeltaPositionListener, public Input::Keyboard::KeyListener
    {
    private:
        math::Radians yaw, pitch;

        void updateTransform(const math::Vec3& position);

    public:
        FPSCamera(const math::Vec3& position, math::Radians yaw, math::Radians pitch);

        void deltaPositionCallback(double deltatime, const std::vector<Input::Mouse::PositionEvent>& positionEvents) override;
        void keyCallback(double deltatime, const std::vector<Input::Keyboard::KeyEvent>& keyEvents) override;
    };
}