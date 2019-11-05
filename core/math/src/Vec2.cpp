#include <math.h>
#include <iostream>
#include <Vec2.h>

namespace math
{
    vec2& vec2::add(const vec2& other)
    {
        x += other.x; y += other.y;
        return *this;
    }

    vec2& vec2::substract(const vec2& other)
    {
        x -= other.x; y -= other.y;;
        return *this;
    }

    vec2& vec2::multiply(const vec2& other)
    {
        x *= other.x; y *= other.y;
        return *this;
    }

    vec2& vec2::divide(const vec2& other)
    {
        x /= other.x; y /= other.y;
        return *this;
    }

    vec2& vec2::add(float scalar)
    {
        x += scalar; y += scalar;
        return *this;
    }

    vec2& vec2::substract(float scalar)
    {
        x -= scalar; y -= scalar;
        return *this;
    }

    vec2& vec2::multiply(float scalar)
    {
        x *= scalar; y *= scalar;
        return *this;
    }

    vec2& vec2::divide(float scalar)
    {
        x /= scalar; y /= scalar;
        return *this;
    }

    vec2& vec2::operator +=(const vec2& other) { return add(other); }
    vec2& vec2::operator -=(const vec2& other) { return substract(other); }
    vec2& vec2::operator *=(const vec2& other) { return multiply(other); }
    vec2& vec2::operator /=(const vec2& other) { return divide(other); }

    vec2& vec2::operator +=(float scalar) { return add(scalar); }
    vec2& vec2::operator -=(float scalar) { return substract(scalar); }
    vec2& vec2::operator *=(float scalar) { return multiply(scalar); }
    vec2& vec2::operator /=(float scalar) { return divide(scalar); }

    vec2& vec2::operator +(const vec2& other) const { return vec2(*this).add(other); }
    vec2& vec2::operator -(const vec2& other) const { return vec2(*this).substract(other); }
    vec2& vec2::operator *(const vec2& other) const { return vec2(*this).multiply(other); }
    vec2& vec2::operator /(const vec2& other) const { return vec2(*this).divide(other); }

    vec2& vec2::operator +(float scalar) const { return vec2(*this).add(scalar); }
    vec2& vec2::operator -(float scalar) const { return vec2(*this).substract(scalar); }
    vec2& vec2::operator *(float scalar) const { return vec2(*this).multiply(scalar); }
    vec2& vec2::operator /(float scalar) const { return vec2(*this).divide(scalar); }
    
    float vec2::magnitude() const { return sqrt(x*x + y*y); }
    float vec2::dot(const vec2& other) const { return x * other.x + y * other.y;}
    float vec2::cross(const vec2& other) const { return x * other.y - y * other.x; }
    vec2 vec2::normalize() const { return *this / magnitude(); }

    std::ostream& operator<<(std::ostream& out, const vec2& vector)
    {
        out << '[';
        
        for(size_t i = 0; i < 2; i++)
            out << vector.elements[i] << (i != 1 ? ", " : "");
        
        out << ']';
        return out;
    }    
}