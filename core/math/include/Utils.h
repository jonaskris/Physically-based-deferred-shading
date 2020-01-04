#pragma once

#include <math.h>

#include <Degrees.h>
#include <Radians.h>

#include <Vec4.h>
#include <Vec3.h>
#include <Vec2.h>

namespace math 
{
    // Angles
    inline float toRadians(float degrees)
    {
        return degrees * (float)(M_PI / 180.0);
    }

    inline float toDegrees(float radians)
    {
        return radians / (float)(M_PI / 180.0);
    }

    // Vector conversions
    inline Vec2 toVec2(const Vec3& v)
    {
        return Vec2(v.elements[0], v.elements[1]);
    }

    inline Vec2 toVec2(const Vec4& v)
    {
        return Vec2(v.elements[0], v.elements[1]);
    }

    inline Vec3 toVec3(const Vec4& v)
    {
        return Vec3(v.elements[0], v.elements[1], v.elements[2]);
    }
}