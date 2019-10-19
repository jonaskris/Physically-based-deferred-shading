#pragma once

namespace math
{
    struct vec2
    {
        union
        {
            float elements[2];
            struct 
            {
                float x, y;
            };
        };

        vec2();
        vec2(float scalar);
        vec2(const vec2& other);
        vec2(float x, float y);

        vec2& add(const vec2& other);
        vec2& substract(const vec2& other);
        vec2& multiply(const vec2& other);
        vec2& divide(const vec2& other);

        vec2& add(float scalar);
        vec2& substract(float scalar);
        vec2& multiply(float scalar);
        vec2& divide(float scalar);

        vec2& operator +=(const vec2& other); 
        vec2& operator -=(const vec2& other); 
        vec2& operator *=(const vec2& other); 
        vec2& operator /=(const vec2& other); 

        vec2& operator +=(float scalar); 
        vec2& operator -=(float scalar); 
        vec2& operator *=(float scalar);
        vec2& operator /=(float scalar); 

        vec2& operator +(const vec2& other) const; 
        vec2& operator -(const vec2& other) const;
        vec2& operator *(const vec2& other) const;
        vec2& operator /(const vec2& other) const;

        vec2& operator +(float scalar) const;
        vec2& operator -(float scalar) const;
        vec2& operator *(float scalar) const;
        vec2& operator /(float scalar) const;

        float magnitude() const;
        float dot(const vec2& other) const;
        float cross(const vec2& other) const;
        vec2 normalize() const;
    };
}