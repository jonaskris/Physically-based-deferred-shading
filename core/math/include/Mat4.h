#pragma once
#include <iostream>
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

        mat4(
            float x0, float y0, float z0, float w0,
            float x1, float y1, float z1, float w1,
            float x2, float y2, float z2, float w2,
            float x3, float y3, float z3, float w3
        );

        mat4(
            vec4 row0,
            vec4 row1,
            vec4 row2,
            vec4 row3
        );

        vec4 getRow(size_t row) const;
        void setRow(size_t row, const vec4& vector);

        mat4& multiply(const mat4& other);
        vec4 multiply(const vec4& vector) const;

        vec4 operator*(const vec4& vector) const;
        mat4 operator*(const mat4& other) const;
        mat4& operator*=(const mat4& other);

        static mat4 identity();
        static mat4 translate(const vec3& vector);
        static mat4 rotate(float angle, const vec3& axis);
        static mat4 scale(const vec3& vector);
		static mat4 perspective(float fov, float aspectratio, float near, float far);
        static mat4 view(const vec3& lookFrom, const vec3& lookAt, const vec3& up);

        friend std::ostream& operator<<(std::ostream& out, const math::mat4& matrix);
    };
}
