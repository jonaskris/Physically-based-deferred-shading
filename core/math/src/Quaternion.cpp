#include <iostream>

#include <math.h>

#include <Quaternion.h>

#include <Vec3.h>
#include <Utils.h>

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

    Quaternion Quaternion::fromEulerAngles(Radians yaw, Radians pitch, Radians roll)
    {        
        //const Quaternion first({0.0f, 1.0f, 0.0f}, yaw);
        //const Quaternion second({0.0f, 0.0f, 1.0f}, pitch);
        //const Quaternion third({1.0f, 0.0f, 0.0f}, roll);
        //
        //return third * second * first;

        double cy = cosf(yaw / 2.0f);
        double sy = sinf(yaw / 2.0f);
        double cp = cosf(pitch / 2.0f);
        double sp = sinf(pitch / 2.0f);
        double cr = cosf(roll / 2.0f);
        double sr = sinf(roll / 2.0f);

        return Quaternion(
            cy * cp * sr - sy * sp * cr,
            sy * cp * sr + cy * sp * cr,
            sy * cp * cr - cy * sp * sr,
            cy * cp * cr + sy * sp * sr
        );
    }

    // Operations
    Quaternion& Quaternion::multiply(const Quaternion& other)
    {
        Vec3 newVector = other.vector * scalar + vector * other.scalar - vector.cross(other.vector);
        float newScalar = scalar * other.scalar - vector.dot(other.vector);

        vector = newVector;
        scalar = newScalar;

        return *this;
    }

    Quaternion& Quaternion::multiply(float scalar)
    {
        this->vector *= scalar;
        this->scalar *= scalar;
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

    Mat4 Quaternion::toMatrix() const
    {
        /*
                                1 - 2*qy2 - 2*qz2,                          2*qx*qy - 2*qz*qw,                          2*qx*qz + 2*qy*qw
                                2*qx*qy + 2*qz*qw,                          1 - 2*qx2 - 2*qz2,                          2*qy*qz - 2*qx*qw
                                2*qx*qz - 2*qy*qw,                          2*qy*qz + 2*qx*qw,                          1 - 2*qx2 - 2*qy2
        */
        return Mat4
        (
            1.0f - 2.0f * vector.elements[1] * vector.elements[1] - 2.0f * vector.elements[2] * vector.elements[2], 2.0f * vector.elements[0] * vector.elements[1] - 2.0f * vector.elements[2] * scalar, 2.0f * vector.elements[0] * vector.elements[2] + 2.0f * vector.elements[1] * scalar, 0.0f,
            2.0f * vector.elements[0] * vector.elements[1] + 2.0f * vector.elements[2] * scalar, 1.0f - 2.0f * vector.elements[0] * vector.elements[0] - 2.0f * vector.elements[2] * vector.elements[2], 2.0f * vector.elements[1] * vector.elements[2] - 2.0f * vector.elements[0] * scalar, 0.0f,
            2.0f * vector.elements[0] * vector.elements[2] - 2.0f * vector.elements[1] * scalar, 2.0f * vector.elements[1] * vector.elements[2] + 2.0f * vector.elements[0] * scalar, 1.0f - 2.0f * vector.elements[0] * vector.elements[0] - 2.0f * vector.elements[1] * vector.elements[1], 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );

        /*
            1.0f - 2.0f * vector.elements[1] * vector.elements[1] - 2.0f * vector.elements[2] * vector.elements[2], 2.0f * vector.elements[0] * vector.elements[1] + 2.0f * vector.elements[2] * scalar, 2.0f * vector.elements[0] * vector.elements[2] - 2.0f * vector.elements[1] * scalar, 0.0f,
            2.0f * vector.elements[0] * vector.elements[1] - 2.0f * vector.elements[2] * scalar, 1.0f - 2.0f * vector.elements[0] * vector.elements[0] - 2.0f * vector.elements[2] * vector.elements[2], 2.0f * vector.elements[1] * vector.elements[2] + 2.0f * vector.elements[0] * scalar, 0.0f,
            2.0f * vector.elements[0] * vector.elements[2] + 2.0f * vector.elements[1] * scalar, 2.0f * vector.elements[1] * vector.elements[2] - 2.0f * vector.elements[0] * scalar, 1.0f - 2.0f * vector.elements[0] * vector.elements[0] - 2.0f * vector.elements[1] * vector.elements[1], 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        */
    }

    
    // Operators
    Quaternion& Quaternion::operator*=(const Quaternion& other) { return multiply(other); }
    Quaternion& Quaternion::operator*=(float scalar) { return multiply(scalar); }
    Quaternion Quaternion::operator*(const Quaternion& other) const { return Quaternion(*this).multiply(other); }
    Quaternion Quaternion::operator*(float scalar) const { return Quaternion(*this).multiply(scalar); }
    
    std::ostream& operator<<(std::ostream& out, const Quaternion& quaternion);
}