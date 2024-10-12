#pragma once

template < array_type type1, array_type type2 >
    requires comparable<typename type1::value_type> and
             std::convertible_to<typename type1::value_type,typename type2::value_type> and
             std::convertible_to<typename type2::value_type,typename type1::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename relu_layer<type1,type2>::output_type relu_layer<type1,type2>::forward ( const input_type& inputs ) const
{
    using value_type = output_type::value_type;

    if constexpr ( input_type::dimension() == 1 )
        return output_type(inputs.size(), [&] (int i) { return std::max(value_type(), inputs[i]); }); // Instead of std::max(0,x) as relu does not requires number_type<value_type>

    else if constexpr ( input_type::dimension() >= 2 )
    {
        output_type result = inputs;
        result.flatten().transform([] (const auto& x) { return std::max(value_type(), x); });
        return result;
    }
}

template < array_type type1, array_type type2 >
    requires comparable<typename type1::value_type> and
             std::convertible_to<typename type1::value_type,typename type2::value_type> and
             std::convertible_to<typename type2::value_type,typename type1::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename relu_layer<type1,type2>::batch_output_type relu_layer<type1,type2>::forward ( const batch_input_type& inputs ) const
{
    return batch_output_type(inputs.row(), [&] (int i) { return self.forward(inputs[i]); });
}

template < array_type type1, array_type type2 >
    requires comparable<typename type1::value_type> and
             std::convertible_to<typename type1::value_type,typename type2::value_type> and
             std::convertible_to<typename type2::value_type,typename type1::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename relu_layer<type1,type2>::output_type relu_layer<type1,type2>::forward ( input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.forward(optimizer.template history_input<input_type>() = std::move(inputs));
}

template < array_type type1, array_type type2 >
    requires comparable<typename type1::value_type> and
             std::convertible_to<typename type1::value_type,typename type2::value_type> and
             std::convertible_to<typename type2::value_type,typename type1::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename relu_layer<type1,type2>::batch_output_type relu_layer<type1,type2>::forward ( batch_input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.forward(optimizer.template history_input<batch_input_type>() = std::move(inputs));
}

template < array_type type1, array_type type2 >
    requires comparable<typename type1::value_type> and
             std::convertible_to<typename type1::value_type,typename type2::value_type> and
             std::convertible_to<typename type2::value_type,typename type1::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename relu_layer<type1,type2>::input_type relu_layer<type1,type2>::backward ( const output_type& losses, optimizer_type auto& optimizer )
{
    let& inputs = optimizer.template history_input<input_type>();
    return self.backward_aux(losses, inputs);
}

template < array_type type1, array_type type2 >
    requires comparable<typename type1::value_type> and
             std::convertible_to<typename type1::value_type,typename type2::value_type> and
             std::convertible_to<typename type2::value_type,typename type1::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr typename relu_layer<type1,type2>::batch_input_type relu_layer<type1,type2>::backward ( const batch_output_type& losses, optimizer_type auto& optimizer )
{
    let& inputs = optimizer.template history_input<batch_input_type>();
    return batch_input_type(inputs.row(), [&] (int i) { return self.backward_aux(losses[i], inputs[i]); });
}

template < array_type type1, array_type type2 >
    requires comparable<typename type1::value_type> and
             std::convertible_to<typename type1::value_type,typename type2::value_type> and
             std::convertible_to<typename type2::value_type,typename type1::value_type> and
             ( type1::dimension() == type2::dimension() )
constexpr auto relu_layer<type1,type2>::backward_aux ( const auto& losses, auto& inputs )
{
    using value_type = input_type::value_type;

    if constexpr ( output_type::dimension() == 1 )
        return input_type(losses.size(), [&] (int i) { return inputs[i] > value_type() ? value_type(losses[i]) otherwise value_type(); });  // Instead of std::max(0,x) as relu does not requires number_type<value_type>

    else if constexpr ( output_type::dimension() >= 2 )
    {
        input_type result = losses;
        for ( int i in range(result.size()) )
            if ( inputs.flatten()[i] <= value_type() )
                result.flatten()[i] = value_type();
        return result;
    }
}
