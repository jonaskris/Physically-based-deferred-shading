#pragma once

namespace math
{
    struct Degrees;
    
    /*
        Radians/Degrees structs provide implicit conversions to each
        other and float type.
    */
    struct Radians
    {
        float radians;
    
        explicit Radians(float radians);
        Radians(const Degrees& degrees);
    
        operator float() const;
    };
}