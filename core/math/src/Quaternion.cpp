#include <Quaternion.h>

#include <math.h>

namespace math
{

    // Initialization
    Quaternion::Quaternion() : vector(0.0f, 0.0f, 0.0f), scalar(1.0f) {}
    Quaternion::Quaternion(float x, float y, float z, float w) : vector{x, y, z}, scalar(w) {}
    Quaternion::Quaternion(const Vec3& vector, float scalar) : vector(vector), scalar(scalar) {}

    Quaternion Quaternion::fromAxisAngle(const Vec3& axis, Radians angle)
    {
        return Quaternion
        (
            {
                axis.elements[0] * sinf(angle / 2.0f),
                axis.elements[1] * sinf(angle / 2.0f),
                axis.elements[2] * sinf(angle / 2.0f)
            },
            cosf(angle / 2.0f)
        );
    }

    Quaternion Quaternion::fromEulerAngles(Radians x, Radians y, Radians z)
    {        
        Quaternion qX = Quaternion::fromAxisAngle({1.0f, 0.0f, 0.0f}, x);
		Quaternion qY = Quaternion::fromAxisAngle({0.0f, 1.0f, 0.0f}, y);
		Quaternion qZ = Quaternion::fromAxisAngle({0.0f, 0.0f, 1.0f}, z);

		return qX * qY * qZ; // XYZ order
    }

    // Operations
    Quaternion& Quaternion::multiply(const Quaternion& other)
    {
        Quaternion temp;
        temp.vector.elements[0] =  vector.elements[0] * other.scalar + vector.elements[1] * other.vector.elements[2] - vector.elements[2] * other.vector.elements[1] + scalar * other.vector.elements[0];
        temp.vector.elements[1] = -vector.elements[0] * other.vector.elements[2] + vector.elements[1] * other.scalar + vector.elements[2] * other.vector.elements[0] + scalar * other.vector.elements[1];
        temp.vector.elements[2] =  vector.elements[0] * other.vector.elements[1] - vector.elements[1] * other.vector.elements[0] + vector.elements[2] * other.scalar + scalar * other.vector.elements[2];
        temp.scalar = -vector.elements[0] * other.vector.elements[0] - vector.elements[1] * other.vector.elements[1] - vector.elements[2] * other.vector.elements[2] + scalar * other.scalar;

        *this = temp;
        return *this;
    }

    Quaternion& Quaternion::multiply(float scalar)
    {
        this->vector *= scalar;
        this->scalar *= scalar;
    }

    Vec3 Quaternion::multiply(const Vec3& vector) const
    {
        return this->vector * 2.0f * this->vector.dot(vector)
                + vector * (scalar*scalar - this->vector.dot(this->vector))
                + this->vector.cross(vector) * 2.0f * scalar;
    }

    float Quaternion::dot(const Quaternion& other) const { return vector.elements[0] * other.vector.elements[0] + vector.elements[1] * other.vector.elements[1] + vector.elements[2] * other.vector.elements[2] + scalar * other.scalar; }
    float Quaternion::magnitude() const { return sqrt(vector.elements[0] * vector.elements[0] + vector.elements[1] * vector.elements[1] + vector.elements[2] * vector.elements[2] + scalar * scalar); }
    Quaternion Quaternion::normalize() const 
    { 
        float mag = magnitude();
        return Quaternion(vector / mag, scalar / mag); 
    }
    Quaternion Quaternion::inverse() const
    {
        float mag = magnitude();
        return Quaternion(-vector, scalar) * (1.0f / (mag * mag));
    }

    Quaternion Quaternion::conjugate() const
    {
        return Quaternion(-vector, scalar);
    }

    Mat4 Quaternion::toMatrix() const
    {
        return Mat4
        (
            1.0f - 2.0f * vector.elements[1] * vector.elements[1] - 2.0f * vector.elements[2] * vector.elements[2], 2.0f * vector.elements[0] * vector.elements[1] - 2.0f * vector.elements[2] * scalar, 2.0f * vector.elements[0] * vector.elements[2] + 2.0f * vector.elements[1] * scalar, 0.0f,
            2.0f * vector.elements[0] * vector.elements[1] + 2.0f * vector.elements[2] * scalar, 1.0f - 2.0f * vector.elements[0] * vector.elements[0] - 2.0f * vector.elements[2] * vector.elements[2], 2.0f * vector.elements[1] * vector.elements[2] - 2.0f * vector.elements[0] * scalar, 0.0f,
            2.0f * vector.elements[0] * vector.elements[2] - 2.0f * vector.elements[1] * scalar, 2.0f * vector.elements[1] * vector.elements[2] + 2.0f * vector.elements[0] * scalar, 1.0f - 2.0f * vector.elements[0] * vector.elements[0] - 2.0f * vector.elements[1] * vector.elements[1], 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    // Operators
    Quaternion& Quaternion::operator*=(const Quaternion& other) { return multiply(other); }
    Quaternion& Quaternion::operator*=(float scalar) { return multiply(scalar); }
    Quaternion Quaternion::operator*(const Quaternion& other) const { return Quaternion(*this).multiply(other); }
    Quaternion Quaternion::operator*(float scalar) const { return Quaternion(*this).multiply(scalar); }
    Vec3 Quaternion::operator*(const Vec3& vector) const { return multiply(vector); }
    
    std::ostream& operator<<(std::ostream& out, const Quaternion& quaternion)
    {
        out << '[';

        for(size_t i = 0; i < 3; i++)
            out << quaternion.vector.elements[i] << ", ";

        out << quaternion.scalar << ']';
    }
}