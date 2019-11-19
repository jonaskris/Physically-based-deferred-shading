#pragma once

#include <math.h>

namespace math 
{
    inline float toRadians(float degrees)
    {
        return degrees * (float)(M_PI / 180.0);
    }
    
    inline float toDegrees(float radians)
    {
        return radians * (float)(180.0 / M_PI);
    }
}