#include <Camera.h>

#include <glad/glad.h>

#include <vector>

#include <Utils.h>
#include <Vec3.h>
#include <Mat4.h>
#include <Transform.h>

#include <Input.h>
#include <Node.h>
#include <Uniform.h>
#include <RenderData.h>
#include <Model.h>

namespace graphics
{
    // Camera
    Camera::Camera(math::Transform transform, std::vector<unsigned int> childrenNodes)
    : Node(transform, childrenNodes) {};

    void Camera::process(GLuint programId, math::Mat4 parentTransform)
    {
        // Set transform
        parentTransform = transform.toMatrix() * parentTransform;

        // Set view
        view = parentTransform.inverse().value();
        Uniform::setMat4(programId, "view", view);

        // Set position
        position = math::toVec3((parentTransform * math::Vec4(0.0f, 0.0f, 0.0f, 1.0f)));

        // Process childrenNodes
        for(unsigned int n : childrenNodes)
        {
            graphics::Node* node = graphics::RenderData::get<graphics::Model>(n);
            if(node)
                node->process(programId, parentTransform);
        }
    }

    math::Mat4 Camera::getView() const
    {
        return view;
    }

    math::Vec3 Camera::getPosition() const
    {
        return position;
    }

    
    // FirstPersonCamera
    FirstPersonCamera::FirstPersonCamera(const math::Vec3& position, math::Radians yaw, math::Radians pitch, std::vector<unsigned int> childrenNodes)
    : yaw(yaw), pitch(pitch),
    Camera(
        math::Transform(position, math::Quaternion::fromEulerAngles(yaw, pitch, math::Radians(0.0f))),
        childrenNodes
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
    
        // Limit yaw to +-360 degrees to limit floating point errors with big values
        yaw.radians = std::fmod(yaw, math::toRadians(360.0f));
        
        // Limit pitch to +-90 degrees
        if(pitch > math::toRadians(89.99f))
            pitch.radians = math::toRadians(89.99f);
        if(pitch < math::toRadians(-89.99f))
            pitch.radians = math::toRadians(-89.99f);
    
        transform.setOrientation(math::Quaternion::fromEulerAngles(math::Radians(-pitch.radians), math::Radians(-yaw.radians), math::Radians(0.0f)));        
    }
    
    void FirstPersonCamera::keyCallback(double deltatime, const std::vector<Input::Keyboard::KeyEvent>& keyEvents)
    {
        using namespace Input::Keyboard;
    
        static const float moveSpeed = 3.0f; // Per second
    
        // Make a frameMoveSpeed based on frame render time, to make input independent of FPS
        const float frameMoveSpeed = moveSpeed * (float)deltatime;
    
        // Limit WASD movement to horizontal plane by using a horizontal forward vector
        math::Vec3 horizontalForward = toVec3(transform.getOrientation().toMatrix() * math::Vec4(0.0f, 0.0f, -1.0f, 0.0f));
        horizontalForward.elements[1] = 0.0f;
        horizontalForward = horizontalForward.normalize();
    
        math::Vec3 position = transform.getPosition();

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

        transform.setPosition(position);
    }
}