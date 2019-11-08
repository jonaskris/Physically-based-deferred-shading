#pragma once
#include <iostream>

namespace math
{
    struct mat4;

    struct vec4
    {
        float elements[4];

        // Initialization
        vec4();
        vec4(float x, float y, float z, float w);

        // Accessors
        float& x();
        float& y();
        float& z();
        float& w();

        // Operations
        vec4& multiply(const mat4& matrix);

        vec4& add(const vec4& other);
        vec4& substract(const vec4& other);
        vec4& multiply(const vec4& other);
        vec4& divide(const vec4& other);

        vec4& add(float scalar);
        vec4& substract(float scalar);
        vec4& multiply(float scalar);
        vec4& divide(float scalar);

        float magnitude() const;
        float dot(const vec4& other) const;
        vec4 normalize() const;

        // Operators
        vec4& operator*=(const mat4& matrix);

        vec4& operator+=(const vec4& other); 
        vec4& operator-=(const vec4& other); 
        vec4& operator*=(const vec4& other); 
        vec4& operator/=(const vec4& other); 

        vec4& operator+=(float scalar); 
        vec4& operator-=(float scalar); 
        vec4& operator*=(float scalar);
        vec4& operator/=(float scalar); 

        vec4 operator*(const mat4& matrix) const;

        vec4 operator+(const vec4& other) const; 
        vec4 operator-(const vec4& other) const;
        vec4 operator*(const vec4& other) const;
        vec4 operator/(const vec4& other) const;

        vec4 operator+(float scalar) const;
        vec4 operator-(float scalar) const;
        vec4 operator*(float scalar) const;
        vec4 operator/(float scalar) const;

        friend std::ostream& operator<<(std::ostream& out, const vec4& vector);
    };
}