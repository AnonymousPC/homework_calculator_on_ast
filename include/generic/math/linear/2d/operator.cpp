#pragma once

/// Declaration

constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( left .dimension() == 2 ) and ( number_type<left_value_type > or complex_type<left_value_type > ) and
             ( right.dimension() == 2 ) and ( number_type<right_value_type> or complex_type<right_value_type> )
{
    #if debug
        if ( left.column() != right.row() )
            throw value_error("cannot multiply matrix of shape {} and matrix of shape {}", left.shape(), right.shape());
    #endif

    try
    {
        using type = std::common_type<left_value_type,right_value_type>::type;
        return aux::from_eigen((aux::to_eigen(left.template as_type<type>()) * aux::to_eigen(right.template as_type<type>())).eval());
    }
    catch ( const std::runtime_error& e )
    {
        throw math_error("cannot multiply matrix: [[from {}]] {}", "eigen", e.what());
    }
}

constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( left .dimension() == 2 ) and ( number_type<left_value_type > or complex_type<left_value_type > ) and
             ( right.dimension() == 1 ) and ( number_type<right_value_type> or complex_type<right_value_type> )
{
    #if debug
        if ( left.column() != right.size() )
            throw value_error("cannot multiply matrix of shape {} and vector of size {}", left.shape(), right.size());
    #endif

    return array ( left.row(), [&] ( int i ) { return dot ( left[i], right ); } );
}

constexpr array_type auto operator * ( const array_type auto& left, const array_type auto& right )
    requires ( left .dimension() == -1 ) and ( number_type<left_value_type > or complex_type<left_value_type > ) and
             ( right.dimension() ==  2 ) and ( number_type<right_value_type> or complex_type<right_value_type> )
{
    #if debug
        if ( left.size() != right.row() )
            throw value_error("cannot multiply matrix of shape {} and vector of size {}", left.shape(), right.size());
    #endif

    let tmp = transpose(right);
    return array ( right.column(), [&] ( int i ) { return dot ( left, tmp[i] ); } );
}

