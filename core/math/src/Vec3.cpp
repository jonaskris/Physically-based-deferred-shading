#include <math.h>
#include <iostream>
#include <Vec3.h>

namespace math
{
    // Operations
    vec3& vec3::add(const vec3& other)
    {
        elements[0] += other.elements[0]; elements[1] += other.elements[1]; elements[2] += other.elements[2];
        return *this;
    }

    vec3& vec3::substract(const vec3& other)
    {
        elements[0] -= other.elements[0]; elements[1] -= other.elements[1]; elements[2] -= other.elements[2];
        return *this;
    }

    vec3& vec3::multiply(const vec3& other)
    {
        elements[0] *= other.elements[0]; elements[1] *= other.elements[1]; elements[2] *= other.elements[2];
        return *this;
    }

    vec3& vec3::divide(const vec3& other)
    {
        elements[0] /= other.elements[0]; elements[1] /= other.elements[1]; elements[2] /= other.elements[2];
        return *this;
    }

    vec3& vec3::add(float scalar)
    {
        elements[0] += scalar; elements[1] += scalar; elements[2] += scalar;
        return *this;
    }

    vec3& vec3::substract(float scalar)
    {
        elements[0] -= scalar; elements[1] -= scalar; elements[2] -= scalar;
        return *this;
    }

    vec3& vec3::multiply(float scalar)
    {
        elements[0] *= scalar; elements[1] *= scalar; elements[2] *= scalar;
        return *this;
    }

    vec3& vec3::divide(float scalar)
    {
        elements[0] /= scalar; elements[1] /= scalar; elements[2] /= scalar;
        return *this;
    }

    float vec3::magnitude() const { return sqrt(elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2]); }
    float vec3::dot(const vec3& other) const { return elements[0] * other.elements[0] + elements[1] * other.elements[1] + elements[2] * other.elements[2]; }
    vec3 vec3::cross(const vec3& other) const { return vec3{elements[1] * other.elements[2] - elements[2] * other.elements[1], elements[2] * other.elements[0] - elements[0] * other.elements[2], elements[0] * other.elements[1] - elements[1] * other.elements[0]}; }
    vec3 vec3::normalize() const { return *this / magnitude(); }

    // Operators
    vec3& vec3::operator+=(const vec3& other) { return add(other); }
    vec3& vec3::operator-=(const vec3& other) { return substract(other); }
    vec3& vec3::operator*=(const vec3& other) { return multiply(other); }
    vec3& vec3::operator/=(const vec3& other) { return divide(other); }

    vec3& vec3::operator+=(float scalar) { return add(scalar); }
    vec3& vec3::operator-=(float scalar) { return substract(scalar); }
    vec3& vec3::operator*=(float scalar) { return multiply(scalar); }
    vec3& vec3::operator/=(float scalar) { return divide(scalar); }

    vec3 vec3::operator+(const vec3& other) const { return vec3(*this).add(other); }
    vec3 vec3::operator-(const vec3& other) const { return vec3(*this).substract(other); }
    vec3 vec3::operator*(const vec3& other) const { return vec3(*this).multiply(other); }
    vec3 vec3::operator/(const vec3& other) const { return vec3(*this).divide(other); }

    vec3 vec3::operator+(float scalar) const { return vec3(*this).add(scalar); }
    vec3 vec3::operator-(float scalar) const { return vec3(*this).substract(scalar); }
    vec3 vec3::operator*(float scalar) const { return vec3(*this).multiply(scalar); }
    vec3 vec3::operator/(float scalar) const { return vec3(*this).divide(scalar); }

    std::ostream& operator<<(std::ostream& out, const vec3& vector)
    {
        out << '[';
        
        for(size_t i = 0; i < 3; i++)
            out << vector.elements[i] << (i != 2 ? ", " : "");
        
        out << ']';
        return out;
    }
}