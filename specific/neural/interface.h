#pragma once
#include "../../generic/math/interface.h"

namespace ap::neural
{
    /// Concept
    template < class type > concept layer_type     = requires { typename type::layer_tag;     };
    template < class type > concept model_type     = requires { typename type::model_tag;     };
    template < class type > concept optimizer_type = requires { typename type::optimizer_tag; };
    template < class type > concept optimizable    = layer_type<type> or model_type<type>;


    /// Layer
    template < array_type type1, array_type type2 > class relu_layer;
    template < array_type type1, array_type type2 > class sigmoid_layer;
    template < array_type type1, array_type type2 > class softmax_layer;
    template < array_type type1, array_type type2 > class convolve_layer;
    template < array_type type1, array_type type2 > class linear_layer;
    template < array_type type1, array_type type2 > class max_pool_layer;

    /// Model
    template < layer_type... types >                class sequence_model;

    /// Optimizer
    template < layer_type... types >                class sgd_optimizer;
    template < layer_type... types >                class adam_optimizer;



    /// Include
    #include "layer/layer.h"
    #include "model/model.h"
    #include "optimizer/optimizer.h"
}
