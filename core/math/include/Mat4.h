#pragma once
#include <iostream>
#include <Utils.h>

namespace math
{
    struct vec3;
    struct vec4;

    struct mat4
    {
        float elements[4*4];

        // Initialization
        mat4();
        mat4(
            float x0, float y0, float z0, float w0,
            float x1, float y1, float z1, float w1,
            float x2, float y2, float z2, float w2,
            float x3, float y3, float z3, float w3
        );
        mat4(
            const vec4& row0,
            const vec4& row1,
            const vec4& row2,
            const vec4& row3
        );

        // Accessors
        vec4 getRow(size_t row) const;
        void setRow(size_t row, const vec4& vector);

        vec4 getColumn(size_t column) const;
        void setColumn(size_t column, const vec4& vector);

        // Operations
        mat4& multiply(const mat4& other);
        vec4 multiply(const vec4& vector) const;

        // Operators
        vec4 operator*(const vec4& vector) const;
        mat4 operator*(const mat4& other) const;
        mat4& operator*=(const mat4& other);
        friend std::ostream& operator<<(std::ostream& out, const math::mat4& matrix);

        // Generators
        static mat4 identity();
        static mat4 translate(const vec3& vector);
        static mat4 rotate(float angle, const vec3& axis);
        static mat4 scale(const vec3& vector);
		static mat4 perspective(float fov, float aspectratio, float near, float far);
        static mat4 view(const vec3& lookFrom, const vec3& lookAt, const vec3& up);
    };
}
