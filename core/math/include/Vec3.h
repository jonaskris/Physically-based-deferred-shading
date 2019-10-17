#pragma once

namespace math
{
    struct vec3
    {
        union
        {
            float elements[3];
            struct 
            {
                float x, y, z;
            };
        };

        vec3();
        vec3(float scalar);
        vec3(const vec3& other);
        vec3(float x, float y, float z);

        vec3& add(const vec3& other);
        vec3& substract(const vec3& other);
        vec3& multiply(const vec3& other);
        vec3& divide(const vec3& other);

        vec3& add(float scalar);
        vec3& substract(float scalar);
        vec3& multiply(float scalar);
        vec3& divide(float scalar);

        vec3& operator +=(const vec3& other); 
        vec3& operator -=(const vec3& other); 
        vec3& operator *=(const vec3& other); 
        vec3& operator /=(const vec3& other); 

        vec3& operator +=(float scalar); 
        vec3& operator -=(float scalar); 
        vec3& operator *=(float scalar);
        vec3& operator /=(float scalar); 

        vec3& operator +(const vec3& other) const; 
        vec3& operator -(const vec3& other) const;
        vec3& operator *(const vec3& other) const;
        vec3& operator /(const vec3& other) const;

        vec3& operator +(float scalar) const;
        vec3& operator -(float scalar) const;
        vec3& operator *(float scalar) const;
        vec3& operator /(float scalar) const;

        float magnitude() const;
        float dot(const vec3& other) const;
        vec3 cross(const vec3& other) const;
        vec3 normalize() const;
    };
}