#pragma once

#define weights self[1c]
#define bias    self[2c]

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type>
constexpr linear_layer<type1,type2>::linear_layer ( int input_size, int output_size )
    extends tuple<matrix<common_type<typename type1::value_type,typename type2::value_type>>,
                  vector<common_type<typename type1::value_type,typename type2::value_type>>>
                ( matrix<common_type<typename type1::value_type,typename type2::value_type>> ( output_size, input_size ),
                  vector<common_type<typename type1::value_type,typename type2::value_type>> ( output_size ) )
{

}





template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type>
constexpr typename linear_layer<type1,type2>::output_type linear_layer<type1,type2>::linear_layer::forward ( const input_type& inputs ) const
{
    return weights * inputs + bias;
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type>
constexpr typename linear_layer<type1,type2>::batch_output_type linear_layer<type1,type2>::linear_layer::forward ( const batch_input_type& inputs ) const
{
    return transpose(weights * transpose(inputs)).each([&] (auto& outputs) { outputs += bias; }); // ( weights * inputs[column-major]] ) [[=> column-major]] + bias[[broadcast]].
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type>
constexpr typename linear_layer<type1,type2>::output_type linear_layer<type1,type2>::linear_layer::forward ( input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.forward(optimizer.template history_input<input_type>() = std::move(inputs));
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type>
constexpr typename linear_layer<type1,type2>::batch_output_type linear_layer<type1,type2>::linear_layer::forward ( batch_input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.forward(optimizer.template history_input<batch_input_type>() = std::move(inputs));
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type>
constexpr typename linear_layer<type1,type2>::input_type linear_layer<type1,type2>::backward ( const output_type& losses, optimizer_type auto& optimizer )
{
    let& inputs = optimizer.template history_input<input_type>();

    let grad_weights = losses * transpose(inputs);
    let grad_bias    = losses;
    let grad_layer   = transpose(weights) * losses;

    weights -= optimizer(std::move(grad_weights));
    bias    -= optimizer(std::move(grad_bias));

    return grad_layer;
}

template < array_type type1, array_type type2 >
    requires float_type<typename type1::value_type> and
             float_type<typename type2::value_type>
constexpr typename linear_layer<type1,type2>::batch_input_type linear_layer<type1,type2>::backward ( const batch_output_type& losses, optimizer_type auto& optimizer )
{
    let& inputs = optimizer.template history_input<batch_input_type>();

    print(losses.shape());

    let grad_weights = transpose(losses) * inputs;                        // losses[[column-major]] * transpose(inputs[[column-major]]).
    let grad_bias    = losses.template sum<2>();                          // losses[[column-major]].sum<1>().
    let grad_layer   = transpose(transpose(weights) * transpose(losses)); // ( transpose(weights) * losses[[column-major]] ) [[=> column-major]].

    weights -= optimizer(std::move(grad_weights));
    bias    -= optimizer(std::move(grad_bias));

    return grad_layer;
}


#undef weights
#undef bias
