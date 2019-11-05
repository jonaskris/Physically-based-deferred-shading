#include <math.h>
#include <iostream>
#include <Vec3.h>

namespace math
{
    vec3& vec3::add(const vec3& other)
    {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    vec3& vec3::substract(const vec3& other)
    {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    vec3& vec3::multiply(const vec3& other)
    {
        x *= other.x; y *= other.y; z *= other.z;
        return *this;
    }

    vec3& vec3::divide(const vec3& other)
    {
        x /= other.x; y /= other.y; z /= other.z;
        return *this;
    }

    vec3& vec3::add(float scalar)
    {
        x += scalar; y += scalar; z += scalar;
        return *this;
    }

    vec3& vec3::substract(float scalar)
    {
        x -= scalar; y -= scalar; z -= scalar;
        return *this;
    }

    vec3& vec3::multiply(float scalar)
    {
        x *= scalar; y *= scalar; z *= scalar;
        return *this;
    }

    vec3& vec3::divide(float scalar)
    {
        x /= scalar; y /= scalar; z /= scalar;
        return *this;
    }

    vec3& vec3::operator +=(const vec3& other) { return add(other); }
    vec3& vec3::operator -=(const vec3& other) { return substract(other); }
    vec3& vec3::operator *=(const vec3& other) { return multiply(other); }
    vec3& vec3::operator /=(const vec3& other) { return divide(other); }

    vec3& vec3::operator +=(float scalar) { return add(scalar); }
    vec3& vec3::operator -=(float scalar) { return substract(scalar); }
    vec3& vec3::operator *=(float scalar) { return multiply(scalar); }
    vec3& vec3::operator /=(float scalar) { return divide(scalar); }

    vec3& vec3::operator +(const vec3& other) const { return vec3(*this).add(other); }
    vec3& vec3::operator -(const vec3& other) const { return vec3(*this).substract(other); }
    vec3& vec3::operator *(const vec3& other) const { return vec3(*this).multiply(other); }
    vec3& vec3::operator /(const vec3& other) const { return vec3(*this).divide(other); }

    vec3& vec3::operator +(float scalar) const { return vec3(*this).add(scalar); }
    vec3& vec3::operator -(float scalar) const { return vec3(*this).substract(scalar); }
    vec3& vec3::operator *(float scalar) const { return vec3(*this).multiply(scalar); }
    vec3& vec3::operator /(float scalar) const { return vec3(*this).divide(scalar); }
    
    float vec3::magnitude() const { return sqrt(x*x + y*y + z*z); }
    float vec3::dot(const vec3& other) const { return x * other.x + y * other.y + z * other.z;}
    vec3 vec3::cross(const vec3& other) const { return vec3{y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x}; }
    vec3 vec3::normalize() const { return *this / magnitude(); }

    std::ostream& operator<<(std::ostream& out, const vec3& vector)
    {
        out << '[';
        
        for(size_t i = 0; i < 3; i++)
            out << vector.elements[i] << (i != 2 ? ", " : "");
        
        out << ']';
        return out;
    }
}