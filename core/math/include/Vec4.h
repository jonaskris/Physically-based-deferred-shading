#pragma once
#include <iostream>

namespace math
{
    struct vec4
    {
        union
        {
            float elements[4];
            struct 
            {
                float x, y, z, w;
            };
        };

        vec4& add(const vec4& other);
        vec4& substract(const vec4& other);
        vec4& multiply(const vec4& other);
        vec4& divide(const vec4& other);

        vec4& add(float scalar);
        vec4& substract(float scalar);
        vec4& multiply(float scalar);
        vec4& divide(float scalar);

        vec4& operator +=(const vec4& other); 
        vec4& operator -=(const vec4& other); 
        vec4& operator *=(const vec4& other); 
        vec4& operator /=(const vec4& other); 

        vec4& operator +=(float scalar); 
        vec4& operator -=(float scalar); 
        vec4& operator *=(float scalar);
        vec4& operator /=(float scalar); 

        vec4& operator +(const vec4& other) const; 
        vec4& operator -(const vec4& other) const;
        vec4& operator *(const vec4& other) const;
        vec4& operator /(const vec4& other) const;

        vec4& operator +(float scalar) const;
        vec4& operator -(float scalar) const;
        vec4& operator *(float scalar) const;
        vec4& operator /(float scalar) const;

        float magnitude() const;
        float dot(const vec4& other) const;
        vec4 normalize() const;

        friend std::ostream& operator<<(std::ostream& out, const vec4& vector);
    };
}