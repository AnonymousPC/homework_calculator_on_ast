#pragma once

constexpr float_type auto sin ( angle_type auto t )
{
    if constexpr ( std::floating_point<typename decltype(t)::value_type> )
        return std::sin(radian(t).value());
    else
        return typename decltype(t)::value_type ( std::sin(float_to_float_type<typename decltype(t)::value_type>(radian(t).value())) );
}

constexpr float_type auto cos ( angle_type auto t )
{
    if constexpr ( std::floating_point<typename decltype(t)::value_type> )
        return std::cos(radian(t).value());
    else
        return typename decltype(t)::value_type ( std::cos(float_to_float_type<typename decltype(t)::value_type>(radian(t).value())) );
}

constexpr float_type auto tan ( angle_type auto t )
{
    if ( abs(mod(t, degree(180))) == degree(90) )
        throw math_error("arg {} is out of domain for {} with {}", t, "tan", "{x|x!=(2k+1)*90deg, k in N}");

    if constexpr ( std::floating_point<typename decltype(t)::value_type> )
        return std::tan(radian(t).value());
    else
        return typename decltype(t)::value_type ( std::tan(float_to_float_type<typename decltype(t)::value_type>(radian(t).value())) );
}

constexpr float_type auto cot ( angle_type auto t )
{
    if ( abs(mod(t, degree(180))) == degree(0) )
        throw math_error("arg {} is out of domain for {} with {}", t, "cot", "{x|x!=(2k)*90deg, k in N}");

    return 1 / tan(t);
}

constexpr float_type auto sec ( angle_type auto t )
{
    if ( abs(mod(t, degree(180))) == degree(90) )
        throw math_error("arg {} is out of domain for {} with {}", t, "sec", "{x|x!=(2k+1)*90deg, k in N}");

    return 1 / cos(t);
}

constexpr float_type auto csc ( angle_type auto t )
{
    if ( abs(mod(t, degree(180))) == degree(0) )
        throw math_error("arg {} is out of domain for {} with {}", t, "csc", "{ x|x!=(2k)*90deg, k in N}");

    return 1 / sin(t);
}












