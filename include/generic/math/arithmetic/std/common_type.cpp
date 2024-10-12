#pragma once

#define left_type  decay<decltype(left )>
#define right_type decay<decltype(right)>




/// Declaration

namespace aux
{
    template < class type >
    concept arithmetic_type = number_type <type> or
                              angle_type  <type> or
                              complex_type<type> or
                              polar_type  <type>;
}

constexpr auto operator == ( const aux::arithmetic_type auto& left, const aux::arithmetic_type auto& right )
    requires ( not std::same_as<left_type,right_type> ) and equalable<left_type> and equalable<right_type> and requires { typename common_type<left_type,right_type>; }
{
    using common = common_type<left_type,right_type>;
    return common(left) == common(right);
}

constexpr auto operator <=> ( const aux::arithmetic_type auto& left, const aux::arithmetic_type auto& right )
    requires ( not std::same_as<left_type,right_type> ) and comparable<left_type> and comparable<right_type> and requires { typename common_type<left_type,right_type>; }
{
    using common = common_type<left_type,right_type>;
    return common(left) <=> common(right);
}

constexpr auto operator + ( const aux::arithmetic_type auto& left, const aux::arithmetic_type auto& right )
    requires ( not std::same_as<left_type,right_type> ) and addable<left_type> and addable<right_type> and requires { typename common_type<left_type,right_type>; }
{
    using common = common_type<left_type,right_type>;
    return common(left) + common(right);
}

constexpr auto operator - ( const aux::arithmetic_type auto& left, const aux::arithmetic_type auto& right )
    requires ( not std::same_as<left_type,right_type> ) and minusable<left_type> and minusable<right_type> and requires { typename common_type<left_type,right_type>; }
{
    using common = common_type<left_type,right_type>;
    return common(left) - common(right);
}

constexpr auto operator * ( const aux::arithmetic_type auto& left, const aux::arithmetic_type auto& right )
    requires ( not std::same_as<left_type,right_type> ) and multipliable<left_type> and multipliable<right_type> and requires { typename common_type<left_type,right_type>; }
{
    using common = common_type<left_type,right_type>;
    return common(left) * common(right);
}

constexpr auto operator / ( const aux::arithmetic_type auto& left, const aux::arithmetic_type auto& right )
    requires ( not std::same_as<left_type,right_type> ) and dividable<left_type> and dividable<right_type> and requires { typename common_type<left_type,right_type>; }
{
    using common = common_type<left_type,right_type>;
    return common(left) / common(right);
}

} // namespace ap







// Class std::common_type

// Fraction

template < ap::fraction_type type1, ap::fraction_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::fraction<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};

template < ap::fraction_type type1, ap::int_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::fraction<typename common_type<typename type1::value_type,type2>::type>;
};

template < ap::fraction_type type1, ap::float_type type2 >
    requires ( not ap::fraction_type<type2> )
struct std::common_type<type1,type2>
{
    using type = type2;
};

template < ap::int_type type1, ap::fraction_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::fraction<typename common_type<type1,typename type2::value_type>::type>;
};

template < ap::float_type type1, ap::fraction_type type2 >
    requires ( not ap::fraction_type<type1> )
struct std::common_type<type1,type2>
{
    using type = type1;
};




// Angle [degree,radian]

template < ap::degree_type type1, ap::degree_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::degree<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};

template < ap::radian_type type1, ap::radian_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::radian<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};

template < ap::degree_type type1, ap::radian_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::radian<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};

template < ap::radian_type type1, ap::degree_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::radian<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};





// Complex

template < ap::complex_type type1, ap::complex_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::complex<typename common_type<typename type1::value_type,typename type2::value_type>::type>;
};

template < ap::complex_type type1, ap::number_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::complex<typename common_type<typename type1::value_type,type2>::type>;
};

template < ap::number_type type1, ap::complex_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::complex<typename common_type<type1,typename type2::value_type>::type>;
};




// Polar

template < ap::polar_type type1, ap::polar_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::polar<typename common_type<typename type1::value_type,typename type2::value_type>::type,
                           typename common_type<typename type1::angle_type,typename type2::angle_type>::type
                          >;
};

template < ap::polar_type type1, ap::number_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::polar<typename common_type<typename type1::value_type,type2>::type,
                           typename                      type1::angle_type       ::type
                          >;
};

template < ap::number_type type1, ap::polar_type type2 >
struct std::common_type<type1,type2>
{
    using type = ap::polar<typename common_type<type1,typename type2::value_type>::type,
                           typename                            type2::angle_type ::type
                          >;
};






namespace ap // Back to namespace ap
{




#undef left_type
#undef right_type






