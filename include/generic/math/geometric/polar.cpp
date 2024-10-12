#pragma once

/// Class polar

template < number_type type1, angle_type type2 >
class polar
{
    private: // Data
        type1 r = 0;
        type2 t = type2();

    public: // Typedef
        using value_type = type1;
        using angle_type = type2;
        struct polar_tag { };

    public: // Core
        constexpr polar ( ) = default;
        constexpr polar ( type1 );
        constexpr polar ( type1, type2 );
        constexpr const type1& abs ( ) const;
        constexpr const type2& arg ( ) const;

    public: // Conversion
        constexpr polar ( number_type  auto );
        constexpr polar ( polar_type   auto );
        constexpr polar ( complex_type auto c ) requires float_type<type1> and float_type<typename decltype(c)::value_type>;

    public: // Operator
        constexpr bool operator == ( const polar& ) const = default;
        constexpr bool operator != ( const polar& ) const = default;
};



/// Template deduction

template < number_type type1 >                   polar ( type1 )        -> polar<type1>;
template < number_type type1, angle_type type2 > polar ( type1, type2 ) -> polar<type1,type2>;



// Core

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2>::polar ( type1 init_r )
    extends r ( init_r )
{

}

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2>::polar ( type1 init_r, type2 init_t )
    extends r ( init_r ),
            t ( init_t )
{

}

template < number_type type1, angle_type type2 >
constexpr const type1& polar<type1,type2>::abs ( ) const
{
    return r;
}

template < number_type type1, angle_type type2 >
constexpr const type2& polar<type1,type2>::arg ( ) const
{
    return t;
}

// Conversion

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2>::polar ( polar_type auto cvt )
    extends polar ( cvt.abs(), cvt.arg() )
{

}

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2>::polar ( number_type auto cvt )
    extends polar ( static_cast<type1>(cvt) )
{

}

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2>::polar ( complex_type auto cvt )
    requires float_type<type1> and float_type<typename decltype(cvt)::value_type>
    extends r ( sqrt ( cvt.real() * cvt.real() + cvt.imag() * cvt.imag() ) )
{
    t = r          == 0 ?   type2 ( 0 )                         otherwise
        cvt.imag() >= 0 ?   type2 ( arccos ( cvt.real() / r ) ) otherwise
                          - type2 ( arccos ( cvt.real() / r ) );
}



/// Global

template < number_type type1, angle_type type2 >
std::ostream& operator << ( std::ostream& left, const polar<type1,type2>& right )
{
    return left << '[' << right.abs() << ',' << right.arg() << ']';
}

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2> operator + ( const polar<type1,type2>& right )
{
    return right;
}

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2> operator - ( const polar<type1,type2>& right )
{
    return polar ( right.abs(), - right.arg() );
}

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2> operator + ( const polar<type1,type2>& left, const polar<type1,type2>& right ) = delete;

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2> operator - ( const polar<type1,type2>& left, const polar<type1,type2>& right ) = delete;

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2> operator * ( const polar<type1,type2>& left, const polar<type1,type2>& right )
{
    return polar ( left.abs() * right.abs(), left.arg() + right.arg() );
}

template < number_type type1, angle_type type2 >
constexpr polar<type1,type2> operator / ( const polar<type1,type2>& left, const polar<type1,type2>& right )
{
    if ( right.abs() == 0 )
        throw math_error("{} / {}", left, right);

    return polar ( left.abs() / right.abs(), left.arg() - right.arg() );
}

