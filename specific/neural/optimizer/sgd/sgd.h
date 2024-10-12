#pragma once

template < layer_type... types >
class sgd_optimizer;

template < layer_type type >
class sgd_optimizer<type>
    extends public type
{
    private: // Precondition
        static_assert ( not std::same_as<typename type::input_type,typename type::batch_input_type> );

    public: // Typedef
        using  input_type       = type::input_type;
        using  batch_input_type = type::batch_input_type;
        struct optimizer_tag { };

    private: // Data
        input_type       history_inputs       = {};
        batch_input_type history_batch_inputs = {};

        float            lr              = 1.0  / 64.0;
        float            mmt             = 63.0 / 64.0;

    public: // Interface
        template < class param_type > constexpr       param_type& operator()    ( param_type )       requires aux::same_as_one_of_tuple_value_type<param_type,type>;
        template < class param_type > constexpr       param_type& history_input ( )                  requires std::same_as<param_type,input_type> or std::same_as<param_type,batch_input_type>;
        template < class param_type > constexpr const param_type& history_input ( )            const requires std::same_as<param_type,input_type> or std::same_as<param_type,batch_input_type>;
};

template < layer_type... types >
class sgd_optimizer
    extends public tuple<sgd_optimizer<types>...>
{
    public: // Typedef
        struct optimizer_tag { };
};


#include "sgd.cpp"
