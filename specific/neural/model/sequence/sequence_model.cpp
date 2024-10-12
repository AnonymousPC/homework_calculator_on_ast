#pragma once

template < layer_type... types >
constexpr sequence_model<types...>::output_type sequence_model<types...>::forward ( const input_type& inputs ) const
{
    return self.tuplewise_forward(inputs);
}

template < layer_type... types >
constexpr sequence_model<types...>::batch_output_type sequence_model<types...>::forward ( const batch_input_type& inputs ) const
{
    return self.tuplewise_forward(inputs);
}

template < layer_type... types >
constexpr sequence_model<types...>::output_type sequence_model<types...>::forward ( input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.tuplewise_forward(std::move(inputs), optimizer);
}

template < layer_type... types >
constexpr sequence_model<types...>::batch_output_type sequence_model<types...>::forward ( batch_input_type inputs, optimizer_type auto& optimizer ) const
{
    return self.tuplewise_forward(std::move(inputs), optimizer);
}

template < layer_type... types >
constexpr void sequence_model<types...>::backward ( const output_type& losses, optimizer_type auto& optimizer )
{
    return self.tuplewise_backward(losses, optimizer);
}

template < layer_type... types >
constexpr void sequence_model<types...>::backward ( const batch_output_type& losses, optimizer_type auto& optimizer )
{
    return self.tuplewise_backward(losses, optimizer);
}


template < layer_type... types >
template < int index >
constexpr auto sequence_model<types...>::tuplewise_forward ( const auto& inputs ) const
{
    if constexpr ( index <= sizeof...(types) )
        return self.tuplewise_forward<index+1> ( self[constexpr_index<index>()].forward(inputs) );
    else
        return inputs;
}

template < layer_type... types >
template < int index >
constexpr auto sequence_model<types...>::tuplewise_forward ( auto inputs, auto& optimizer ) const
{
    if constexpr ( index <= sizeof...(types) )
        return self.tuplewise_forward<index+1> ( self[constexpr_index<index>()].forward(std::move(inputs), optimizer[constexpr_index<index>()]) );
    else
        return inputs;
}

template < layer_type... types >
template < int index >
constexpr void sequence_model<types...>::tuplewise_backward ( const auto& losses, auto& optimizer )
{
    if constexpr ( index >= 1 )
        return self.tuplewise_backward<index-1> ( self[constexpr_index<index>()].backward(losses, optimizer[constexpr_index<index>()]), optimizer);
}





