#pragma once
#include "../array/array.h"



/// Class

template < class char_type >
class basic_string;

template < class char_type >
class basic_string_range_view;

template < class char_type >
class basic_string_view;




/// Regex

template < class char_type >
class basic_regex;



/// Algo

template < class string_type, class char_type >
class string_algo;



/// Include

// In folder "string_base"
#include "string_base/string_global.h" // First.
#include "string_base/string_algo.h"
#include "string_base/string_regex.h"

// In folder "string_class"
#include "string_class/basic_string.h"

// In folder "string_view"
#include "string_view/basic_string_range_view.h"
#include "string_view/basic_string_view.h"

