#pragma once

// Macro.begin
#ifdef debug
    #if debug
        #define tmp_debug_symbol
    #endif
    #undef debug
#endif

#ifdef release
    #if release
        #define tmp_release_symbol
    #endif
    #undef release
#endif

#ifdef dll
    #if dll
        #define tmp_dll_symbol
    #endif
    #undef dll
#endif

// Include [[std]]
#define __cpp_lib_text_encoding 202306L
#include <algorithm>
#include <chrono>
#include <concepts>
#include <csignal>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <new>
#include <ranges>
#include <regex>
#include <stacktrace>
#include <stdfloat>
#include <string>
#include <text_encoding>
#include <thread>
#include <utility>

// Include [[std.experimental.execution]]
#pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wshadow"
    #pragma GCC diagnostic ignored "-Wswitch-default"
    #pragma GCC diagnostic ignored "-Wundef"
    #pragma GCC diagnostic ignored "-Wunused-parameter"
    #include <stdexec/execution.hpp>
    #include <exec/static_thread_pool.hpp>
    #include <tbbexec/tbb_thread_pool.hpp>
#pragma GCC diagnostic pop

// Include [[compiler.gcc, compiler.clang]]
#if defined(__GNUC__) or defined(__clang__)
    #include <cxxabi.h>
#endif

// Include [[system.windows]]
#ifdef _WIN32
    #include <windows.h>
    #include <winhttp.h>
#endif

// Include [[hardware.tbb]]
#include <tbb/tbb.h>

// Include [[third-party.boost]]
#include <boost/date_time.hpp>
#include <boost/locale.hpp>
#include <boost/phoenix.hpp>
#include <boost/spirit/home/qi.hpp>
#include <boost/spirit/home/x3.hpp>

// Include [[third-party.eigen]]
#define eigen_assert(x) do { if ( not Eigen::internal::copy_bool(x) ) throw std::runtime_error(EIGEN_MAKESTRING(x)); } while ( false )
#include <eigen3/Eigen/Eigen>
#include <eigen3/unsupported/Eigen/FFT>

// Macro.end
#ifdef tmp_debug_symbol
    #undef tmp_debug_symbol
    #define debug true
#endif

#ifdef tmp_release_symbol
    #undef tmp_release_symbol
    #define release true
#endif

#ifdef tmp_dll_symbol
    #undef tmp_dll_symbol
    #define dll true
#endif





// Compiler
#ifdef __GNUC__
    #pragma GCC diagnostic ignored "-Wliteral-suffix"  // Allowing user-defined literal without being warned that literal not begins with '_' is kept for further standarlization.
    #pragma GCC diagnostic ignored "-Wredundant-decls" // Allowing declaration of non-template functions many times.
    #pragma GCC diagnostic ignored "-Wswitch-default"  // Has bug with co_yeild.
#endif

// Logic
#define abstract 0    // Usage: virtual int func() = abstract;
#define but and       // Usage: while ( x > 0 but x < 100 ) ...
#define extends :     // Usage: class array extends pubic array_algo { };
#define in :          // Usage: for ( auto element in array ) ...
#define let auto      // Usage: let x = 1;
#define otherwise :   // Usage: x > y ? print("yes") otherwise print("no");
#define self (*this)  // Usage: self[1] = 100;

namespace ap
{
    /// Subnamespace
    inline namespace constants { }
    inline namespace literals  { }

    namespace abi       { }
    namespace neural    { }
    namespace spirit    { }
    namespace stock     { }

    /// Class
    template < class type, bool continuous > class range;

    /// Concept
    template < class input_type, class value_type = void > concept range_type = [] { if constexpr ( requires { typename input_type::range_tag; } ) { if constexpr ( std::is_void<value_type>::value ) return true; else return std::same_as<typename input_type::value_type,value_type>; } else return false; } ();
    // More omitted... see concept.h.

    /// Abi
    namespace abi
    {
        constexpr std::string demangle ( const char* );
        constexpr std::string demangle ( const auto& stacktrace ) requires requires { stacktrace.begin()->description(); stacktrace.begin()->source_file(); stacktrace.begin()->source_line(); };
    }

    /// Exception
    class exception;
        class logic_error;
            class value_error;
            class index_error;
            class key_error;
            class nullptr_error;

        class runtime_error;
            class type_error;
            class format_error;
            class regex_error;
            class file_error;
            class network_error;
            class math_error;


        class signal;
            class abort_signal;                    // Uncathable by father-classes.
            class floating_point_exception_signal;
            class illegal_instruction_signal;
            class interrupt_signal;
            class segmentation_violation_signal;
            class terminate_signal;                // Uncathable by father-classes.

    /// Function
    /* lambda function */ // void print ( const printable auto&... );
    /* lambda function */ // auto input ( const printable auto&... );

    /// Include
    #include "abi.h"
    #include "concept.h"
    #include "exception.h"
    #include "range.h"
    #include "typedef.h"
    #include "utility.h"

    /// Initialize
    class global_initializer_type
    {
        public: // Interface
            global_initializer_type ( )
            {
                // Standard.print
                std::ios_base::sync_with_stdio(false);
                std::cout << std::boolalpha;
                // Standard.signal
                std::signal(SIGABRT, abort_signal);
                std::signal(SIGFPE,  floating_point_exception_signal);
                std::signal(SIGILL,  illegal_instruction_signal);
                std::signal(SIGINT,  interrupt_signal);
                std::signal(SIGSEGV, segmentation_violation_signal);
                std::signal(SIGTERM, terminate_signal);

                // Windows
                #ifdef _WIN32
                    SetConsoleCP      (CP_UTF8);
                    SetConsoleOutputCP(CP_UTF8);
                #endif
            }

        private: // Functions
            static void abort_signal                    ( int ) { throw ap::abort_signal();                    };
            static void floating_point_exception_signal ( int ) { throw ap::floating_point_exception_signal(); };
            static void illegal_instruction_signal      ( int ) { throw ap::illegal_instruction_signal();      };
            static void interrupt_signal                ( int ) { throw ap::interrupt_signal();                };
            static void segmentation_violation_signal   ( int ) { throw ap::segmentation_violation_signal();   };
            static void terminate_signal                ( int ) { throw ap::terminate_signal();                };
    };

    global_initializer_type global_initializer;

} // namespace ap



/// Standard experimental import

namespace std
{
    // [[std.experimental.execution]]
    namespace execution
    {
        using namespace ::stdexec;
        using namespace ::exec;
        using namespace ::tbbexec;
     // using namespace ::nvexec;
    }
}

namespace ap
{
    auto  global_cpu_executor  = std::execution::tbb_thread_pool(20);
    auto  global_cpu_scheduler = global_cpu_executor.get_scheduler();
    auto& global_gpu_executor  = global_cpu_executor;
    auto& global_gpu_scheduler = global_cpu_scheduler;
}
