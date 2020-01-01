#pragma once

#include <math.h>

#include <Degrees.h>
#include <Radians.h>

namespace math 
{
    inline float toRadians(float degrees)
    {
        return degrees * (float)(M_PI / 180.0);
    }

    inline float toDegrees(float radians)
    {
        return radians / (float)(M_PI / 180.0);
    }
}