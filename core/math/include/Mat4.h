#pragma once

#include <iostream>
#include <optional>

#include <Utils.h>

namespace math
{
    struct Vec3;
    struct Vec4;

    struct Mat4
    {
        float elements[4*4];

        // Initialization
        Mat4(float diagonal);
        Mat4();
        Mat4(
            float x0, float y0, float z0, float w0,
            float x1, float y1, float z1, float w1,
            float x2, float y2, float z2, float w2,
            float x3, float y3, float z3, float w3
        );

        // Accessors
        Vec4 getRow(size_t row) const;
        void setRow(size_t row, const Vec4& vector);

        Vec4 getColumn(size_t column) const;
        void setColumn(size_t column, const Vec4& vector);

        // Operations
        Mat4& multiply(const Mat4& other);
        Vec4 multiply(const Vec4& vector) const;
        std::optional<Mat4> inverse() const;

        // Operators
        Vec4 operator*(const Vec4& vector) const;
        Mat4 operator*(const Mat4& other) const;
        Mat4& operator*=(const Mat4& other);
        friend std::ostream& operator<<(std::ostream& out, const math::Mat4& matrix);

        // Generators
        static Mat4 identity();
        static Mat4 translate(const Vec3& vector);
        static Mat4 rotate(Radians angle, const Vec3& axis);
        static Mat4 scale(const Vec3& vector);

        static Mat4 perspective(float left, float right, float bottom, float top, float near, float far);   // Non-symmetric
		static Mat4 perspective(Radians fov, float aspectratio, float near, float far);                       // Symmetric with fov and aspectratio

        static Mat4 view(const Vec3& lookFrom, const Vec3& lookAt, const Vec3& up);
    };
}
