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

    // radians = degrees * (M_PI / 180.0f)
    // degrees = radians / (M_PI / 180.0f)
    
    inline float toDegrees(float radians)
    {
        return radians / (float)(M_PI / 180.0);
    }
}