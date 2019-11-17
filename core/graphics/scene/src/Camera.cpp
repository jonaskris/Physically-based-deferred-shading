#include <Vec2.h>
#include <Vec3.h>
#include <Mat4.h>
#include <Uniform.h>
#include <Camera.h>

// Camera
Camera::Camera(const math::vec3& lookFrom, const math::vec3& lookAt, const math::vec3& up)
: lookFrom(lookFrom), lookAt(lookAt), up(up), view({"view", math::mat4::view(lookFrom, lookAt, up)}) {};

void Camera::setUniforms(GLuint programId)
{
    view.setMatrix(math::mat4::view(lookFrom, lookAt, up));
    view.set(programId);
}

// FirstPersonCamera
FirstPersonCamera::FirstPersonCamera(const math::vec3& lookFrom, const math::vec3& up, float yaw, float pitch) : yaw(yaw), pitch(pitch),
forward
({
    cosf(math::toRadians(pitch)) * cosf(math::toRadians(yaw)),
    sinf(math::toRadians(pitch)),
    cosf(math::toRadians(pitch)) * sinf(-math::toRadians(yaw))
}),
Camera(
    lookFrom, 
    lookFrom + math::vec3
    {
        cosf(math::toRadians(pitch)) * cosf(math::toRadians(yaw)),
        sinf(math::toRadians(pitch)),
        cosf(math::toRadians(pitch)) * sinf(-math::toRadians(yaw))
    },
    up
) {

    //std::cout << "lookFrom: " << lookFrom << ", lookAt: " << lookAt << ", up: " << up << std::endl;
    //std::cin.get();
}

void FirstPersonCamera::positionCallback(math::vec2 position)
{
    static math::vec2 lastPosition{0.5f, 0.5f};
    math::vec2 deltaPos = position - lastPosition;

    // Update yaw and pitch based on input
    yaw -= deltaPos.elements[0] * 10.0f;
    pitch += deltaPos.elements[1] * 10.0f;

    // Limit yaw to -180 to 180 to limit floating point errors with big values.
    yaw = std::fmod(yaw, 180.0f);

    // Limit pitch to a 180 degreee arch.
    if(pitch > 89.99f)
        pitch = 89.99f;
    if(pitch < -89.99f)
        pitch = -89.99f;

    // Update forward vector
    forward =
    {
        cosf(math::toRadians(pitch)) * cosf(math::toRadians(yaw)),
        sinf(math::toRadians(pitch)),
        cosf(math::toRadians(pitch)) * sinf(-math::toRadians(yaw))
    };

    // Update lookAt vector
    lookAt = lookFrom + forward;

    // Update lastPosition
    lastPosition = position;
}

void FirstPersonCamera::keyCallback(const KeyEvent keyEvent)
{
    static const float moveSpeed = 0.1f;

    std::cout << "key: " << (size_t)keyEvent.key << ", action: " << (size_t)keyEvent.action << std::endl;

    if(keyEvent.action == input::keyboard::action::PRESS)
    {
        switch(keyEvent.key)
        {
        case input::keyboard::key::S:
            lookFrom.elements[2] -= moveSpeed;
            break;
        case input::keyboard::key::W:
            lookFrom.elements[2] += moveSpeed;                
            break;
        case input::keyboard::key::A:
            lookFrom.elements[0] -= moveSpeed;                
            break;        
        case input::keyboard::key::D:
            lookFrom.elements[0] += moveSpeed;                
            break;
        case input::keyboard::key::R:
            lookFrom.elements[1] += moveSpeed;                
            break;
        case input::keyboard::key::F:
            lookFrom.elements[1] -= moveSpeed;                
            break;
        
        }
    }

    lookAt = lookFrom + forward;

    //std::cout << "lookFrom: " << lookFrom << std::endl;
}