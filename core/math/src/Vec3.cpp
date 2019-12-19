#include <math.h>
#include <iostream>

#include <Vec3.h>

namespace math
{

    // Initialization
    Vec3::Vec3() : elements{} {}
    Vec3::Vec3(float x, float y, float z) : elements{x, y , z} {}

    // Operations
    Vec3& Vec3::add(const Vec3& other)
    {
        elements[0] += other.elements[0]; elements[1] += other.elements[1]; elements[2] += other.elements[2];
        return *this;
    }

    Vec3& Vec3::substract(const Vec3& other)
    {
        elements[0] -= other.elements[0]; elements[1] -= other.elements[1]; elements[2] -= other.elements[2];
        return *this;
    }

    Vec3& Vec3::multiply(const Vec3& other)
    {
        elements[0] *= other.elements[0]; elements[1] *= other.elements[1]; elements[2] *= other.elements[2];
        return *this;
    }

    Vec3& Vec3::divide(const Vec3& other)
    {
        elements[0] /= other.elements[0]; elements[1] /= other.elements[1]; elements[2] /= other.elements[2];
        return *this;
    }

    Vec3& Vec3::add(float scalar)
    {
        elements[0] += scalar; elements[1] += scalar; elements[2] += scalar;
        return *this;
    }

    Vec3& Vec3::substract(float scalar)
    {
        elements[0] -= scalar; elements[1] -= scalar; elements[2] -= scalar;
        return *this;
    }

    Vec3& Vec3::multiply(float scalar)
    {
        elements[0] *= scalar; elements[1] *= scalar; elements[2] *= scalar;
        return *this;
    }

    Vec3& Vec3::divide(float scalar)
    {
        elements[0] /= scalar; elements[1] /= scalar; elements[2] /= scalar;
        return *this;
    }

    Vec3 Vec3::negate() const
    {
        return Vec3(-elements[0], -elements[1], -elements[2]);
    }

    float Vec3::magnitude() const { return sqrt(elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2]); }
    float Vec3::dot(const Vec3& other) const { return elements[0] * other.elements[0] + elements[1] * other.elements[1] + elements[2] * other.elements[2]; }
    Vec3 Vec3::cross(const Vec3& other) const { return Vec3{elements[1] * other.elements[2] - elements[2] * other.elements[1], elements[2] * other.elements[0] - elements[0] * other.elements[2], elements[0] * other.elements[1] - elements[1] * other.elements[0]}; }
    Vec3 Vec3::normalize() const { return *this / magnitude(); }

    // Operators
    Vec3& Vec3::operator+=(const Vec3& other) { return add(other); }
    Vec3& Vec3::operator-=(const Vec3& other) { return substract(other); }
    Vec3& Vec3::operator*=(const Vec3& other) { return multiply(other); }
    Vec3& Vec3::operator/=(const Vec3& other) { return divide(other); }

    Vec3& Vec3::operator+=(float scalar) { return add(scalar); }
    Vec3& Vec3::operator-=(float scalar) { return substract(scalar); }
    Vec3& Vec3::operator*=(float scalar) { return multiply(scalar); }
    Vec3& Vec3::operator/=(float scalar) { return divide(scalar); }

    Vec3 Vec3::operator-() const { return negate(); }

    Vec3 Vec3::operator+(const Vec3& other) const { return Vec3(*this).add(other); }
    Vec3 Vec3::operator-(const Vec3& other) const { return Vec3(*this).substract(other); }
    Vec3 Vec3::operator*(const Vec3& other) const { return Vec3(*this).multiply(other); }
    Vec3 Vec3::operator/(const Vec3& other) const { return Vec3(*this).divide(other); }

    Vec3 Vec3::operator+(float scalar) const { return Vec3(*this).add(scalar); }
    Vec3 Vec3::operator-(float scalar) const { return Vec3(*this).substract(scalar); }
    Vec3 Vec3::operator*(float scalar) const { return Vec3(*this).multiply(scalar); }
    Vec3 Vec3::operator/(float scalar) const { return Vec3(*this).divide(scalar); }

    std::ostream& operator<<(std::ostream& out, const Vec3& vector)
    {
        out << '[';
        
        for(size_t i = 0; i < 3; i++)
            out << vector.elements[i] << (i != 2 ? ", " : "");
        
        out << ']';
        return out;
    }
}