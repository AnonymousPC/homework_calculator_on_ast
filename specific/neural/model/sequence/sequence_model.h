#pragma once

template < layer_type... types >
class sequence_model
    extends public tuple<types...>
{
    private: // Precondition
        static_assert ( aux::chain_invocable<types...> );

    public: // Typedef
        using input_type        = first_type_of<types...>::input_type;
        using batch_input_type  = first_type_of<types...>::batch_input_type;
        using output_type       = last_type_of <types...>::output_type;
        using batch_output_type = last_type_of <types...>::batch_output_type;

    public: // Interface
        constexpr output_type       forward    ( const input_type&       )                        const;
        constexpr batch_output_type forward    ( const batch_input_type& )                        const;
        constexpr output_type       forward    (       input_type,         optimizer_type auto& ) const;
        constexpr batch_output_type forward    (       batch_input_type,   optimizer_type auto& ) const;
        constexpr void              backward   ( const output_type&,       optimizer_type auto& );
        constexpr void              backward   ( const batch_output_type&, optimizer_type auto& );

    private: // Auxiliary
        template < int index = 1 >                constexpr auto tuplewise_forward  ( const auto& )        const;
        template < int index = 1 >                constexpr auto tuplewise_forward  (       auto,  auto& ) const;
        template < int index = sizeof...(types) > constexpr void tuplewise_backward ( const auto&, auto& );
};

#include "sequence_model.cpp"
