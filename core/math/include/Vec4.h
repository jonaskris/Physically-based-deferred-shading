#pragma once

#include <iostream>

namespace math
{
    struct Mat4;

    struct Vec4
    {
        float elements[4];

        // Initialization
        Vec4();
        Vec4(float x, float y, float z, float w);

        // Accessors
        float& x();
        float& y();
        float& z();
        float& w();

        // Operations
        Vec4& multiply(const Mat4& matrix);

        Vec4& add(const Vec4& other);
        Vec4& substract(const Vec4& other);
        Vec4& multiply(const Vec4& other);
        Vec4& divide(const Vec4& other);

        Vec4& add(float scalar);
        Vec4& substract(float scalar);
        Vec4& multiply(float scalar);
        Vec4& divide(float scalar);

        Vec4 negate() const;

        float magnitude() const;
        float dot(const Vec4& other) const;
        Vec4 normalize() const;

        // Operators
        Vec4& operator*=(const Mat4& matrix);

        Vec4& operator+=(const Vec4& other); 
        Vec4& operator-=(const Vec4& other); 
        Vec4& operator*=(const Vec4& other); 
        Vec4& operator/=(const Vec4& other); 

        Vec4& operator+=(float scalar); 
        Vec4& operator-=(float scalar); 
        Vec4& operator*=(float scalar);
        Vec4& operator/=(float scalar); 

        Vec4 operator-() const;

        Vec4 operator*(const Mat4& matrix) const;

        Vec4 operator+(const Vec4& other) const; 
        Vec4 operator-(const Vec4& other) const;
        Vec4 operator*(const Vec4& other) const;
        Vec4 operator/(const Vec4& other) const;

        Vec4 operator+(float scalar) const;
        Vec4 operator-(float scalar) const;
        Vec4 operator*(float scalar) const;
        Vec4 operator/(float scalar) const;

        friend std::ostream& operator<<(std::ostream& out, const Vec4& vector);
    };
}