#include <vector>
#include <mat4.h>

namespace math
{
    class Transform
    {
    private:
        std::vector<mat4> transforms;

    public:
        Transform(const std::vector<mat4>& transforms) : transforms(transforms) {};

        mat4 toMatrix()
        {
            mat4 returnMatrix = mat4::identity();

            for(const mat4& transform : transforms)
                returnMatrix *= transforms[i];

            return returnMatrix;
        }
    };
}