#pragma once

template < layer_type type >
template < class param_type >
constexpr param_type& sgd_optimizer<type>::operator() ( param_type prm )
    requires aux::same_as_one_of_tuple_value_type<param_type,type>
{
    return self[constexpr_index<aux::index_of_same_type_in_tuple_value_types<param_type,type>>()] = std::move(prm *= lr);
}

template < layer_type type >
template < class param_type >
constexpr param_type& sgd_optimizer<type>::history_input ( )
    requires std::same_as<param_type,input_type> or std::same_as<param_type,batch_input_type>
{
    if constexpr ( std::same_as<param_type,input_type> )
        return self.history_inputs;

    else if constexpr ( std::same_as<param_type,batch_input_type> )
        return self.history_batch_inputs;
}

template < layer_type type >
template < class param_type >
constexpr const param_type& sgd_optimizer<type>::history_input ( ) const
    requires std::same_as<param_type,input_type> or std::same_as<param_type,batch_input_type>
{
    if constexpr ( std::same_as<param_type,input_type> )
        return self.history_inputs;

    else if constexpr ( std::same_as<param_type,batch_input_type> )
        return self.history_batch_inputs;
}

