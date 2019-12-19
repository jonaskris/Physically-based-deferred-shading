#pragma once

#include <iostream>

namespace math
{
    struct Vec3
    {
        float elements[3];

        // Initialization
        Vec3();
        Vec3(float x, float y, float z);

        // Accessors
        float& x();
        float& y();
        float& z();

        // Operations
        Vec3& add(const Vec3& other);
        Vec3& substract(const Vec3& other);
        Vec3& multiply(const Vec3& other);
        Vec3& divide(const Vec3& other);

        Vec3& add(float scalar);
        Vec3& substract(float scalar);
        Vec3& multiply(float scalar);
        Vec3& divide(float scalar);

        Vec3 negate() const;

        float magnitude() const;
        float dot(const Vec3& other) const;
        Vec3 cross(const Vec3& other) const;
        Vec3 normalize() const;

        // Operators
        Vec3& operator+=(const Vec3& other); 
        Vec3& operator-=(const Vec3& other); 
        Vec3& operator*=(const Vec3& other); 
        Vec3& operator/=(const Vec3& other); 

        Vec3& operator+=(float scalar); 
        Vec3& operator-=(float scalar); 
        Vec3& operator*=(float scalar);
        Vec3& operator/=(float scalar); 

        Vec3 operator-() const;

        Vec3 operator+(const Vec3& other) const; 
        Vec3 operator-(const Vec3& other) const;
        Vec3 operator*(const Vec3& other) const;
        Vec3 operator/(const Vec3& other) const;

        Vec3 operator+(float scalar) const;
        Vec3 operator-(float scalar) const;
        Vec3 operator*(float scalar) const;
        Vec3 operator/(float scalar) const;

        friend std::ostream& operator<<(std::ostream& out, const Vec3& vector);
    };
}