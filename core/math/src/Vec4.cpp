#include <cstring>
#include <math.h>
#include <iostream>

#include <Vec4.h>

#include <Mat4.h>

namespace math
{
    // Initialization
    Vec4::Vec4() : elements{} {}
    Vec4::Vec4(float x, float y, float z, float w) : elements{x, y, z, w} {}

    // Operations
    Vec4& Vec4::multiply(const Mat4& matrix)
    {
        Vec4 temp;

        temp.elements[0] = elements[0] * matrix.elements[0]  + elements[1] * matrix.elements[1]  + elements[2] * matrix.elements[2]  + elements[3] * matrix.elements[3];
        temp.elements[1] = elements[0] * matrix.elements[4]  + elements[1] * matrix.elements[5]  + elements[2] * matrix.elements[6]  + elements[3] * matrix.elements[7];
        temp.elements[2] = elements[0] * matrix.elements[8]  + elements[1] * matrix.elements[9]  + elements[2] * matrix.elements[10] + elements[3] * matrix.elements[11];
        temp.elements[3] = elements[0] * matrix.elements[12] + elements[1] * matrix.elements[13] + elements[2] * matrix.elements[14] + elements[3] * matrix.elements[15];
        
        memcpy(elements, temp.elements, 4 * sizeof(float));
        return *this;
    }
    
    Vec4& Vec4::add(const Vec4& other)
    {
        elements[0] += other.elements[0]; elements[1] += other.elements[1]; elements[2] += other.elements[2]; elements[3] += other.elements[3];
        return *this;
    }

    Vec4& Vec4::substract(const Vec4& other)
    {
        elements[0] -= other.elements[0]; elements[1] -= other.elements[1]; elements[2] -= other.elements[2]; elements[3] -= other.elements[3];
        return *this;
    }

    Vec4& Vec4::multiply(const Vec4& other)
    {
        elements[0] *= other.elements[0]; elements[1] *= other.elements[1]; elements[2] *= other.elements[2]; elements[3] *= other.elements[3];
        return *this;
    }

    Vec4& Vec4::divide(const Vec4& other)
    {
        elements[0] /= other.elements[0]; elements[1] /= other.elements[1]; elements[2] /= other.elements[2]; elements[3] /= other.elements[3];
        return *this;
    }

    Vec4& Vec4::add(float scalar)
    {
        elements[0] += scalar; elements[1] += scalar; elements[2] += scalar; elements[3] += scalar;
        return *this;
    }

    Vec4& Vec4::substract(float scalar)
    {
        elements[0] -= scalar; elements[1] -= scalar; elements[2] -= scalar; elements[3] -= scalar;
        return *this;
    }

    Vec4& Vec4::multiply(float scalar)
    {
        elements[0] *= scalar; elements[1] *= scalar; elements[2] *= scalar; elements[3] *= scalar;
        return *this;
    }

    Vec4& Vec4::divide(float scalar)
    {
        elements[0] /= scalar; elements[1] /= scalar; elements[2] /= scalar; elements[3] /= scalar;
        return *this;
    }

    Vec4 Vec4::negate() const
    {
        return Vec4(-elements[0], -elements[1], -elements[2], -elements[3]);
    }

    float Vec4::magnitude() const { return sqrt(elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2] + elements[3] * elements[3]); }
    float Vec4::dot(const Vec4& other) const { return elements[0] * other.elements[0] + elements[1] * other.elements[1] + elements[2] * other.elements[2] + elements[3] * other.elements[3]; }
    Vec4 Vec4::normalize() const { return *this / magnitude(); }

    // Operators
    Vec4& Vec4::operator*=(const Mat4& matrix) { return multiply(matrix); }

    Vec4& Vec4::operator+=(const Vec4& other) { return add(other); }
    Vec4& Vec4::operator-=(const Vec4& other) { return substract(other); }
    Vec4& Vec4::operator*=(const Vec4& other) { return multiply(other); }
    Vec4& Vec4::operator/=(const Vec4& other) { return divide(other); }

    Vec4& Vec4::operator+=(float scalar) { return add(scalar); }
    Vec4& Vec4::operator-=(float scalar) { return substract(scalar); }
    Vec4& Vec4::operator*=(float scalar) { return multiply(scalar); }
    Vec4& Vec4::operator/=(float scalar) { return divide(scalar); }

    Vec4 Vec4::operator-() const { return negate(); }

    Vec4 Vec4::operator*(const Mat4& matrix) const { return Vec4(*this).multiply(matrix); }

    Vec4 Vec4::operator+(const Vec4& other) const { return Vec4(*this).add(other); }
    Vec4 Vec4::operator-(const Vec4& other) const { return Vec4(*this).substract(other); }
    Vec4 Vec4::operator*(const Vec4& other) const { return Vec4(*this).multiply(other); }
    Vec4 Vec4::operator/(const Vec4& other) const { return Vec4(*this).divide(other); }

    Vec4 Vec4::operator+(float scalar) const { return Vec4(*this).add(scalar); }
    Vec4 Vec4::operator-(float scalar) const { return Vec4(*this).substract(scalar); }
    Vec4 Vec4::operator*(float scalar) const { return Vec4(*this).multiply(scalar); }
    Vec4 Vec4::operator/(float scalar) const { return Vec4(*this).divide(scalar); }

    std::ostream& operator<<(std::ostream& out, const Vec4& vector)
    {
        out << '[';
        
        for(size_t i = 0; i < 4; i++)
            out << vector.elements[i] << (i != 3 ? ", " : "");
        
        out << ']';
        return out;
    }
}