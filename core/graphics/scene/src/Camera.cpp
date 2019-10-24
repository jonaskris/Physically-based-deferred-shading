#include <Vec3.h>
#include <Mat4.h>
#include <Uniform.h>
#include <Camera.h>


Camera::Camera(const math::vec3& lookFrom, const math::vec3& lookAt, const math::vec3& up) : UniformMat4f("view", math::mat4::view(lookFrom, lookAt, up)) {};

void Camera::update() { setMatrix(math::mat4::view(lookFrom, lookAt, up)); };