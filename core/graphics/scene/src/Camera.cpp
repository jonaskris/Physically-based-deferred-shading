#include <Vec3.h>
#include <Mat4.h>
#include <Uniform.h>
#include <Camera.h>


Camera::Camera(const math::vec3& lookFrom, const math::vec3& lookAt, const math::vec3& up, float fov, float aspectratio, float near, float far)
 : lookFrom(lookFrom), lookAt(lookAt), up(up), fov(fov), aspectratio(aspectratio), near(near), far(far), view("view", math::mat4::view(lookFrom, lookAt, up)),
   projection("projection", math::mat4::perspective(fov, aspectratio, near, far)) {};

void Camera::setUniforms(GLuint programId)
{
    view.setMatrix(math::mat4::view(lookFrom, lookAt, up));
    projection.setMatrix(math::mat4::perspective(fov, aspectratio, near, far));

    view.set(programId);
    projection.set(programId);
}