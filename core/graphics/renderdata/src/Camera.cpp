#include <Camera.h>

#include <Utils.h>
#include <Vec3.h>
#include <Mat4.h>
#include <Uniform.h>

namespace graphics
{
    // Anonymous "private" namespace for camera helper methods
    namespace 
    {
        math::Vec3 euleranglesToDirectionvector(math::Radians yaw, math::Radians pitch)
        {
            return math::Vec3
            {
                cosf(pitch) * cosf(yaw),
                sinf(pitch),
                cosf(pitch) * sinf(-yaw)
            };
        }
    }
    // Camera
    Camera::Camera(const math::Vec3& lookFrom, const math::Vec3& lookAt, const math::Vec3& up)
    : lookFrom(lookFrom), lookAt(lookAt), up(up), view(math::Mat4::view(lookFrom, lookAt, up)) {};

    void Camera::process(GLuint programId)
    {
        view = math::Mat4::view(lookFrom, lookAt, up);
        Uniform::setMat4(programId, "view", view);
    }
    
    // FirstPersonCamera
    FirstPersonCamera::FirstPersonCamera(const math::Vec3& lookFrom, const math::Vec3& up, math::Radians yaw, math::Radians pitch) : yaw(yaw), pitch(pitch),
    forward( euleranglesToDirectionvector(yaw, pitch) ),
    Camera(
        lookFrom, 
        lookFrom + euleranglesToDirectionvector(yaw, pitch),
        up
    ) {}
    
    void FirstPersonCamera::deltaPositionCallback(double deltatime, const std::vector<Input::Mouse::PositionEvent>& deltaPositionEvents)
    {
        using namespace Input::Mouse;
    
        static const float moveSpeed = 1.0f;
    
        for(auto& deltaPositionEvent : deltaPositionEvents)
        {
            // Update yaw and pitch based on input
            yaw.radians -= deltaPositionEvent.position.elements[0] * moveSpeed;
            pitch.radians += deltaPositionEvent.position.elements[1] * moveSpeed;
        }
    
        // Limit yaw to 360 degrees to limit floating point errors with big values.
        yaw.radians = std::fmod(yaw, 360.0f);
    
        // Limit pitch to a 180 degreee arch.
        if(pitch > math::toRadians(89.99f))
            pitch.radians = math::toRadians(89.99f);
        if(pitch < math::toRadians(-89.99f))
            pitch.radians = math::toRadians(-89.99f);
    
        // Update forward vector
        forward = euleranglesToDirectionvector(yaw, pitch);
    
        // Update lookAt vector
        lookAt = lookFrom + forward;
    }
    
    void FirstPersonCamera::keyCallback(double deltatime, const std::vector<Input::Keyboard::KeyEvent>& keyEvents)
    {
        using namespace Input::Keyboard;
    
        static const float moveSpeed = 3.0f; // Per second
    
        // Make a frameMoveSpeed based on frame render time, to make input independent of FPS
        const float frameMoveSpeed = moveSpeed * (float)deltatime;
    
        // Limit WASD movement to horizontal plane by using a horizontal forward vector
        math::Vec3 horizontalForward = forward;
        horizontalForward.elements[1] = 0.0f;
        horizontalForward = horizontalForward.normalize();
    
        for(auto& keyEvent : keyEvents)
        {
            if(keyEvent.action == Action::HOLD)
            {
                switch(keyEvent.key)
                {
                case Key::S:
                    lookFrom -= horizontalForward * frameMoveSpeed;
                    break;
                case Key::W:
                    lookFrom += horizontalForward * frameMoveSpeed;
                    break;
                case Key::A:
                    lookFrom -= horizontalForward.cross(up) * frameMoveSpeed;
                    break;        
                case Key::D:
                    lookFrom += horizontalForward.cross(up) * frameMoveSpeed;
                    break;
                case Key::SPACE:
                    lookFrom.elements[1] += frameMoveSpeed;                
                    break;
                case Key::LEFT_SHIFT:
                    lookFrom.elements[1] -= frameMoveSpeed;                
                    break;
                }
            }
        }
    
        // Update lookAt so its always relative to lookFrom
        lookAt = lookFrom + forward;
    }
}