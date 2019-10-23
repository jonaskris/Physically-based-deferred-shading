#include <Vec3.h>
#include <Mat4.h>
#include <Uniform.h>

class Camera : public UniformMat4f
{
protected:
    Camera(const math::mat4& view) : UniformMat4f("view", view) {};

public:
    virtual void update() = 0;
};

class Basic_Camera : public Camera
{
public:
    math::vec3 lookFrom;
    math::vec3 lookAt;
    math::vec3 up;

    Basic_Camera(const math::vec3& lookFrom, const math::vec3& lookAt, const math::vec3& up = math::vec3(0.0f, 0.0f, 1.0f)) 
    : Camera(math::mat4::view(lookFrom, lookAt, up)), lookFrom(lookFrom), lookAt(lookAt), up(up) : {};

    void update()
    {
        setMatrix(math::mat4::view(lookFrom, lookAt, up));
    }
};