#pragma once
#include <iostream>

namespace math
{
    struct vec3
    {
        float elements[3] = {};

        // Accessors
        float& x();
        float& y();
        float& z();

        // Operations
        vec3& add(const vec3& other);
        vec3& substract(const vec3& other);
        vec3& multiply(const vec3& other);
        vec3& divide(const vec3& other);

        vec3& add(float scalar);
        vec3& substract(float scalar);
        vec3& multiply(float scalar);
        vec3& divide(float scalar);

        float magnitude() const;
        float dot(const vec3& other) const;
        vec3 cross(const vec3& other) const;
        vec3 normalize() const;

        // Operators
        vec3& operator+=(const vec3& other); 
        vec3& operator-=(const vec3& other); 
        vec3& operator*=(const vec3& other); 
        vec3& operator/=(const vec3& other); 

        vec3& operator+=(float scalar); 
        vec3& operator-=(float scalar); 
        vec3& operator*=(float scalar);
        vec3& operator/=(float scalar); 

        vec3 operator+(const vec3& other) const; 
        vec3 operator-(const vec3& other) const;
        vec3 operator*(const vec3& other) const;
        vec3 operator/(const vec3& other) const;

        vec3 operator+(float scalar) const;
        vec3 operator-(float scalar) const;
        vec3 operator*(float scalar) const;
        vec3 operator/(float scalar) const;

        friend std::ostream& operator<<(std::ostream& out, const vec3& vector);
    };
}