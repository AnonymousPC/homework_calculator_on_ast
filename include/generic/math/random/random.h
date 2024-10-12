#pragma once

/// Include

#include "engine/random_engine_algo.cpp" // First.
#include "engine/linear_congruential_engine.cpp"
#include "engine/mersenne_twister_engine.cpp"
#include "engine/subtract_with_carry_engine.cpp"
#include "engine/discard_block_engine.cpp"
#include "engine/shuffle_order_engine.cpp"
#include "engine/floating_point_engine.cpp"

thread_local mt19937 global_random_engine = mt19937 ( std::random_device()() );

#include "container/array.cpp"
#include "distribution/uniform_distribution.cpp"
#include "distribution/random.cpp"
#include "distribution/bernoulli_distribution.cpp"
#include "distribution/binomial_distribution.cpp"
#include "distribution/geometric_distribution.cpp"
#include "distribution/poisson_distribution.cpp"
#include "distribution/exponential_distribution.cpp"
#include "distribution/gamma_distribution.cpp"
#include "distribution/normal_distribution.cpp"
#include "distribution/chi_squared_distribution.cpp"
#include "distribution/fisher_f_distribution.cpp"
#include "distribution/student_t_distribution.cpp"



