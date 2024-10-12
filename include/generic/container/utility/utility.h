#pragma once

/// Class

template < auto... digits >
class constexpr_index;


/// Function

let input = [] { string str; char buff; while(true) { buff = std::cin.get(); if ( buff != '\n' ) str.push(buff); else break; } return str; };


/// Include

#include "constexpr_index/constexpr_index.h"

} // Out of namespace ap
#include "format/format.h"
#include "structured_binding/structured_binding.h"
namespace ap { // Back into namespace ap
