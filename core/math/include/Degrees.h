#pragma once

namespace math
{
    struct Radians;
    
    /*
        Degrees/Radians structs provide implicit conversions to each
        other and float type.
    */
    struct Degrees
    {
        float degrees;
    
        explicit Degrees(float degrees);
        Degrees(const Radians& radians);
    
        operator float() const;
    };
}