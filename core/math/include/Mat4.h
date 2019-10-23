#pragma once
#include <Utils.h>
#include <Vec4.h>

namespace math
{
    struct vec3;

    struct mat4
    {
        union
        {
            float elements[4*4];
            vec4 columns[4];
        };

        mat4();
        mat4(const mat4& other);

        mat4& multiply(const mat4& other);
        vec4 multiply(const vec4& vector) const;

        vec4 operator *(const vec4& vector) const;
        mat4 operator *(const mat4& other) const;
        mat4& operator *=(const mat4& other);

        static mat4 identity();
        static mat4 translate(const vec3& vector);
        static mat4 rotate(float angle, const vec3& axis);
        static mat4 scale(const vec3& vector);
		static mat4 perspective(float fov, float aspectRatio, float near, float far);
        static mat4 view(const vec3& lookFrom, const vec3& lookAt, const vec3& up);
    };
}