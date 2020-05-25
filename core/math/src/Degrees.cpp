#include "Degrees.h"

#include <math.h>

#include <Utils.h>
#include "Radians.h"

namespace math
{
    Degrees::Degrees(float degrees) : degrees(degrees) {}
    Degrees::Degrees(const Radians& radians) : degrees(toDegrees(radians)) {}

    Degrees Degrees::operator-() const { return Degrees(-degrees); }   

    Degrees::operator float() const
    {
       return degrees;
    }
}