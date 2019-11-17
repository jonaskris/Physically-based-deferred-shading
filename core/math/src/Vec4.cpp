#include <cstring>
#include <math.h>
#include <iostream>

#include <Vec4.h>
#include <Mat4.h>

namespace math
{
    // Operations
    vec4& vec4::multiply(const mat4& matrix)
    {
        vec4 temp;

        temp.elements[0] = elements[0] * matrix.elements[0]  + elements[1] * matrix.elements[1]  + elements[2] * matrix.elements[2]  + elements[3] * matrix.elements[3];
        temp.elements[1] = elements[0] * matrix.elements[4]  + elements[1] * matrix.elements[5]  + elements[2] * matrix.elements[6]  + elements[3] * matrix.elements[7];
        temp.elements[2] = elements[0] * matrix.elements[8]  + elements[1] * matrix.elements[9]  + elements[2] * matrix.elements[10] + elements[3] * matrix.elements[11];
        temp.elements[3] = elements[0] * matrix.elements[12] + elements[1] * matrix.elements[13] + elements[2] * matrix.elements[14] + elements[3] * matrix.elements[15];
        
        memcpy(elements, temp.elements, 4 * sizeof(float));
        return *this;
    }
    
    vec4& vec4::add(const vec4& other)
    {
        elements[0] += other.elements[0]; elements[1] += other.elements[1]; elements[2] += other.elements[2]; elements[3] += other.elements[3];
        return *this;
    }

    vec4& vec4::substract(const vec4& other)
    {
        elements[0] -= other.elements[0]; elements[1] -= other.elements[1]; elements[2] -= other.elements[2]; elements[3] -= other.elements[3];
        return *this;
    }

    vec4& vec4::multiply(const vec4& other)
    {
        elements[0] *= other.elements[0]; elements[1] *= other.elements[1]; elements[2] *= other.elements[2]; elements[3] *= other.elements[3];
        return *this;
    }

    vec4& vec4::divide(const vec4& other)
    {
        elements[0] /= other.elements[0]; elements[1] /= other.elements[1]; elements[2] /= other.elements[2]; elements[3] /= other.elements[3];
        return *this;
    }

    vec4& vec4::add(float scalar)
    {
        elements[0] += scalar; elements[1] += scalar; elements[2] += scalar; elements[3] += scalar;
        return *this;
    }

    vec4& vec4::substract(float scalar)
    {
        elements[0] -= scalar; elements[1] -= scalar; elements[2] -= scalar; elements[3] -= scalar;
        return *this;
    }

    vec4& vec4::multiply(float scalar)
    {
        elements[0] *= scalar; elements[1] *= scalar; elements[2] *= scalar; elements[3] *= scalar;
        return *this;
    }

    vec4& vec4::divide(float scalar)
    {
        elements[0] /= scalar; elements[1] /= scalar; elements[2] /= scalar; elements[3] /= scalar;
        return *this;
    }

    float vec4::magnitude() const { return sqrt(elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2] + elements[3] * elements[3]); }
    float vec4::dot(const vec4& other) const { return elements[0] * other.elements[0] + elements[1] * other.elements[1] + elements[2] * other.elements[2] + elements[3] * other.elements[3]; }
    vec4 vec4::normalize() const { return *this / magnitude(); }

    // Operators
    vec4& vec4::operator*=(const mat4& matrix) { return multiply(matrix); }

    vec4& vec4::operator+=(const vec4& other) { return add(other); }
    vec4& vec4::operator-=(const vec4& other) { return substract(other); }
    vec4& vec4::operator*=(const vec4& other) { return multiply(other); }
    vec4& vec4::operator/=(const vec4& other) { return divide(other); }

    vec4& vec4::operator+=(float scalar) { return add(scalar); }
    vec4& vec4::operator-=(float scalar) { return substract(scalar); }
    vec4& vec4::operator*=(float scalar) { return multiply(scalar); }
    vec4& vec4::operator/=(float scalar) { return divide(scalar); }

    vec4 vec4::operator*(const mat4& matrix) const { return vec4(*this).multiply(matrix); }

    vec4 vec4::operator+(const vec4& other) const { return vec4(*this).add(other); }
    vec4 vec4::operator-(const vec4& other) const { return vec4(*this).substract(other); }
    vec4 vec4::operator*(const vec4& other) const { return vec4(*this).multiply(other); }
    vec4 vec4::operator/(const vec4& other) const { return vec4(*this).divide(other); }

    vec4 vec4::operator+(float scalar) const { return vec4(*this).add(scalar); }
    vec4 vec4::operator-(float scalar) const { return vec4(*this).substract(scalar); }
    vec4 vec4::operator*(float scalar) const { return vec4(*this).multiply(scalar); }
    vec4 vec4::operator/(float scalar) const { return vec4(*this).divide(scalar); }

    std::ostream& operator<<(std::ostream& out, const vec4& vector)
    {
        out << '[';
        
        for(size_t i = 0; i < 4; i++)
            out << vector.elements[i] << (i != 3 ? ", " : "");
        
        out << ']';
        return out;
    }
}