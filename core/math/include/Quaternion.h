#pragma once

#include <iostream>

#include <gtest/gtest.h>

#include <Utils.h>
#include <Vec3.h> 
#include <Mat4.h>

namespace math
{
    struct Quaternion
    {
        FRIEND_TEST(Operations, Magnitude);
        FRIEND_TEST(Operations, Dot);
        FRIEND_TEST(Operations, Normalize);

        Vec3 vector;
        float scalar;

        // Initialization
    private:
        Quaternion(const Vec3& vector, float scalar);
        Quaternion(float x, float y, float z, float w);

    public:
        Quaternion(); // Multiplicative identity

        static Quaternion fromAxisAngle(const Vec3& axis, Radians angle);         // Axis and angle to rotate around that axis
        static Quaternion fromEulerAngles(Radians yaw, Radians pitch, Radians roll);

        // Operations
        Quaternion& multiply(const Quaternion& other);
        Quaternion& multiply(float scalar);

        float dot(const Quaternion& other) const;
        float magnitude() const;
        Quaternion normalize() const;
        Quaternion inverse() const;

        Mat4 toMatrix() const;
        
        // Operators
        Quaternion& operator*=(const Quaternion& other); 
        Quaternion& operator*=(float scalar); 
        
        Quaternion operator*(const Quaternion& other) const;
        Quaternion operator*(float scalar) const;
        
        friend std::ostream& operator<<(std::ostream& out, const Quaternion& quaternion);
    };
}