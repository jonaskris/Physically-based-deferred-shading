#pragma once

#include <iostream>

namespace math
{
    struct Vec2
    {
        float elements[2];

        // Initialization
        Vec2();
        Vec2(float x, float y);

        // Accessors
        float& x();
        float& y();
        float& z();
        
        // Operations
        Vec2& add(const Vec2& other);
        Vec2& substract(const Vec2& other);
        Vec2& multiply(const Vec2& other);
        Vec2& divide(const Vec2& other);

        Vec2& add(float scalar);
        Vec2& substract(float scalar);
        Vec2& multiply(float scalar);
        Vec2& divide(float scalar);

        Vec2 negate() const;

        float magnitude() const;
        float dot(const Vec2& other) const;
        float cross(const Vec2& other) const;
        Vec2 normalize() const;

        // Operators
        Vec2& operator+=(const Vec2& other); 
        Vec2& operator-=(const Vec2& other); 
        Vec2& operator*=(const Vec2& other); 
        Vec2& operator/=(const Vec2& other); 

        Vec2& operator+=(float scalar); 
        Vec2& operator-=(float scalar); 
        Vec2& operator*=(float scalar);
        Vec2& operator/=(float scalar); 

        Vec2 operator-() const;

        Vec2 operator+(const Vec2& other) const; 
        Vec2 operator-(const Vec2& other) const;
        Vec2 operator*(const Vec2& other) const;
        Vec2 operator/(const Vec2& other) const;

        Vec2 operator+(float scalar) const;
        Vec2 operator-(float scalar) const;
        Vec2 operator*(float scalar) const;
        Vec2 operator/(float scalar) const;

        friend std::ostream& operator<<(std::ostream& out, const Vec2& vector);
    };
}