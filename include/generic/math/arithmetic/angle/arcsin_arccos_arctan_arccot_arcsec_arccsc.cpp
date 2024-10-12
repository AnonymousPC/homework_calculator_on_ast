#pragma once

constexpr angle_type auto arcsin ( float_type auto k )
{
    if ( k < -1 or k > 1 )
        throw math_error("arg {} is out of range for {} with {}", k, "arcsin", "[-1,1]");

    if constexpr ( std::floating_point<decltype(k)> )
        return radian ( std::asin(k) );
    else
        return radian<decltype(k)> ( std::asin(float_to_float_type<decltype(k)>(k)) );
}

constexpr angle_type auto arccos ( float_type auto k )
{
    if ( k < -1 or k > 1 )
        throw math_error("arg {} is out of range for {} with {}", k, "arccos", "[-1,1]");

    if constexpr ( std::floating_point<decltype(k)> )
        return radian ( std::acos(k) );
    else
        return radian<decltype(k)> ( std::acos(float_to_float_type<decltype(k)>(k)) );
}

constexpr angle_type auto arctan ( float_type auto k )
{
    if constexpr ( std::floating_point<decltype(k)> )
        return radian ( std::atan(k) );
    else
        return radian<decltype(k)> ( std::atan(float_to_float_type<decltype(k)>(k)) );
}

constexpr angle_type auto arccot ( float_type auto k )
{
    return arctan(1/k);
}

constexpr angle_type auto arcsec ( float_type auto k )
{
    if ( k > -1 or k < 1 )
        throw math_error("arg {} is out of range for {} with {}", k, "arcsec", "(-inf,-1]|[1,+inf)");

    return arccos(1/k);
}

constexpr angle_type auto arccsc ( float_type auto k )
{
    if ( k > -1 or k < 1 )
        throw math_error("arg {} is out of range for {} with {}", k, "arccsc", "(-inf,-1]|[1,+inf)");

    return arcsin(1/k);
}
