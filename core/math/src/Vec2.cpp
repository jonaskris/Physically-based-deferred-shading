#include <math.h>
#include <iostream>

#include <Vec2.h>

namespace math
{

    // Initialization
    Vec2::Vec2() : elements{} {}
    Vec2::Vec2(float x, float y) : elements{x, y} {}

    // Accessors
    float& Vec2::x() { return elements[0]; }
    float& Vec2::y() { return elements[1]; }

    // Operations
    Vec2& Vec2::add(const Vec2& other)
    {
        elements[0] += other.elements[0]; elements[1] += other.elements[1];
        return *this;
    }

    Vec2& Vec2::substract(const Vec2& other)
    {
        elements[0] -= other.elements[0]; elements[1] -= other.elements[1];
        return *this;
    }

    Vec2& Vec2::multiply(const Vec2& other)
    {
        elements[0] *= other.elements[0]; elements[1] *= other.elements[1];
        return *this;
    }

    Vec2& Vec2::divide(const Vec2& other)
    {
        elements[0] /= other.elements[0]; elements[1] /= other.elements[1];
        return *this;
    }

    Vec2& Vec2::add(float scalar)
    {
        elements[0] += scalar; elements[1] += scalar;
        return *this;
    }

    Vec2& Vec2::substract(float scalar)
    {
        elements[0] -= scalar; elements[1] -= scalar;
        return *this;
    }

    Vec2& Vec2::multiply(float scalar)
    {
        elements[0] *= scalar; elements[1] *= scalar;
        return *this;
    }

    Vec2& Vec2::divide(float scalar)
    {
        elements[0] /= scalar; elements[1] /= scalar;
        return *this;
    }

    Vec2 Vec2::negate() const
    {
        return Vec2(-elements[0], -elements[1]);
    }

    float Vec2::magnitude() const { return sqrt(elements[0] * elements[0] + elements[1] * elements[1]); }
    float Vec2::dot(const Vec2& other) const { return elements[0] * other.elements[0] + elements[1] * other.elements[1]; }
    float Vec2::cross(const Vec2& other) const { return elements[0] * other.elements[1] - elements[1] * other.elements[0]; }
    Vec2 Vec2::normalize() const { return *this / magnitude(); }

    // Operators
    Vec2& Vec2::operator+=(const Vec2& other) { return add(other); }
    Vec2& Vec2::operator-=(const Vec2& other) { return substract(other); }
    Vec2& Vec2::operator*=(const Vec2& other) { return multiply(other); }
    Vec2& Vec2::operator/=(const Vec2& other) { return divide(other); }

    Vec2& Vec2::operator+=(float scalar) { return add(scalar); }
    Vec2& Vec2::operator-=(float scalar) { return substract(scalar); }
    Vec2& Vec2::operator*=(float scalar) { return multiply(scalar); }
    Vec2& Vec2::operator/=(float scalar) { return divide(scalar); }

    Vec2 Vec2::operator-() const { return negate(); }

    Vec2 Vec2::operator+(const Vec2& other) const { return Vec2(*this).add(other); }
    Vec2 Vec2::operator-(const Vec2& other) const { return Vec2(*this).substract(other); }
    Vec2 Vec2::operator*(const Vec2& other) const { return Vec2(*this).multiply(other); }
    Vec2 Vec2::operator/(const Vec2& other) const { return Vec2(*this).divide(other); }

    Vec2 Vec2::operator+(float scalar) const { return Vec2(*this).add(scalar); }
    Vec2 Vec2::operator-(float scalar) const { return Vec2(*this).substract(scalar); }
    Vec2 Vec2::operator*(float scalar) const { return Vec2(*this).multiply(scalar); }
    Vec2 Vec2::operator/(float scalar) const { return Vec2(*this).divide(scalar); }

    std::ostream& operator<<(std::ostream& out, const Vec2& vector)
    {
        out << '[';
        
        for(size_t i = 0; i < 2; i++)
            out << vector.elements[i] << (i != 1 ? ", " : "");
        
        out << ']';
        return out;
    }    
}