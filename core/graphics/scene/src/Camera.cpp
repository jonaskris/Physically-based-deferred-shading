#include <Camera.h>

namespace graphics
{
    void Camera::updateViewMatrix() 
    {
        viewMatrix = transform.toMatrix().inverse().value();   
    }

    math::Mat4 Camera::getViewMatrix() 
    {
        if(viewDirty)
        {
            updateViewMatrix();
            viewDirty = false;
        }
 
        return viewMatrix; 
    }

    const math::Transform& Camera::getTransform() const { return transform; }

    void Camera::setTransform(const math::Transform& transform)
    {
        this->transform = transform;
        viewDirty = true;
    }

    math::Vec3 Camera::getPosition() const { return transform.getPosition(); }

    AnimatedCamera::AnimatedCamera(std::function<math::Transform (double)> animationFunc) : animationFunc(animationFunc) {}

    void AnimatedCamera::timeCallback(const Input::Time::TimeEvent& timeEvent)
    {
        setTransform(animationFunc(timeEvent.time));
    }

    void FPSCamera::updateTransform(const math::Vec3& position)
    {
        math::Transform newTransform = getTransform();

        setTransform(math::Transform(position, math::Quaternion::fromEulerAngles(math::Radians(-pitch.radians), math::Radians(-yaw.radians), math::Radians(0.0f))));
    }

    FPSCamera::FPSCamera(const math::Vec3& position, math::Radians yaw, math::Radians pitch) : yaw(yaw), pitch(pitch)
    {
        updateTransform(position);
    }
    
    void FPSCamera::deltaPositionCallback(double deltatime, const std::vector<Input::Mouse::PositionEvent>& deltaPositionEvents)
    {        
        using namespace Input::Mouse;
    
        static const float moveSpeed = 1.0f;
    
        for(auto& deltaPositionEvent : deltaPositionEvents)
        {
            // Update yaw and pitch based on input
            yaw.radians -= deltaPositionEvent.position.elements[0] * moveSpeed;
            pitch.radians += deltaPositionEvent.position.elements[1] * moveSpeed;
        }
    
        // Limit yaw to +-360 degrees to limit floating point errors with big values
        yaw.radians = std::fmod(yaw, math::toRadians(360.0f));
        
        // Limit pitch to +-90 degrees
        if(pitch > math::toRadians(89.99f))
            pitch.radians = math::toRadians(89.99f);
        if(pitch < math::toRadians(-89.99f))
            pitch.radians = math::toRadians(-89.99f);

        updateTransform(getTransform().getPosition());    
    }
    
    void FPSCamera::keyCallback(double deltatime, const std::vector<Input::Keyboard::KeyEvent>& keyEvents)
    {
        using namespace Input::Keyboard;
    
        static const float moveSpeed = 3.0f; // Per second
    
        // Make a frameMoveSpeed based on frame render time, to make input independent of FPS
        const float frameMoveSpeed = moveSpeed * (float)deltatime;
    
        // Limit WASD movement to horizontal plane by using a horizontal forward vector
        math::Vec3 horizontalForward = toVec3(getTransform().getOrientation().toMatrix() * math::Vec4(0.0f, 0.0f, -1.0f, 0.0f));
        horizontalForward.elements[1] = 0.0f;
        horizontalForward = horizontalForward.normalize();
    
        math::Vec3 position = getTransform().getPosition();

        for(auto& keyEvent : keyEvents)
        {
            if(keyEvent.action == Action::HOLD)
            {
                switch(keyEvent.key)
                {
                case Key::S:
                    position -= horizontalForward * frameMoveSpeed;
                    break;
                case Key::W:
                    position += horizontalForward * frameMoveSpeed;
                    break;
                case Key::A:
                    position -= horizontalForward.cross({0.0f, 1.0f, 0.0f}) * frameMoveSpeed;
                    break;        
                case Key::D:
                    position += horizontalForward.cross({0.0f, 1.0f, 0.0f}) * frameMoveSpeed;
                    break;
                case Key::SPACE:
                    position.elements[1] += frameMoveSpeed;                
                    break;
                case Key::LEFT_SHIFT:
                    position.elements[1] -= frameMoveSpeed;                
                    break;
                }
            }
        }

        updateTransform(position);
    }
}