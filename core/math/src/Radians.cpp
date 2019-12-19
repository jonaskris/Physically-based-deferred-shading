#include "Radians.h"

#include <math.h>

#include <Utils.h>
#include "Degrees.h"

namespace math
{
    Radians::Radians(float radians) : radians(radians) {}
    Radians::Radians(const Degrees& degrees) : radians(toRadians(degrees)) {}
    
    Radians::operator float() const
    {
       return radians;
    }
}