#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"


// interv-1
// - switch condition inline init with fn call cpp17
// - answer: test 1

// interv-2
// - assign switch result into a var in place like Rust match
// - answer: test 3




// ----------------------------------------------------------------------





#include <string_view>
#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include <string>

#include "utils.h"

// 1. allowed types:
// - Integral types:
    // int
    // char
    // short
    // long
    // long long
    // Their unsigned variants
// - Enumeration types:
    // Plain enums
    // Scoped enums (enum class)

// 2. disallowed types:
// floating-point types (float, double)
// string types

// 3. Notes
// Case values must be compile-time constants

// 4. break alternatives:
// Use break as the default choice
// Use return when you need to exit the function
// Use [[fallthrough]] when you intentionally want fall-through behavior
    // tells compiler/clang-tidy: no break is intentional, do not warning
// goto - avoid it

// 5. Default clause
// - default is optional but recommended as a catch-all
// - can be placed anywhere, not just at the end (but end is convention)

// 6. Variable declaration in cases
// - declaring variables inside cases requires a scope block {}
// case 1:
//     { int x = 5; break; } // ok
// case 2:
//     int x = 5; break;     // error: jumps over initialization
//
// see example below in test 0

TEST_CASE("sw-0") {
    int x = 42;
    switch(x) {
        case 0:
            println("-- 0");
            // break;
            [[fallthrough]];  
                // to compiler/clang-tidy: no break is intentional
        case 42: { // braces are needed due to line " int z .. ",
                   // w/o braces error
            println("-- 42");
            [[maybe_unused]]
            int z = 3;
            break;
        }
        default:
            println("-- Unknown");
            break;
    };
}

TEST_CASE("sw-1") {
    auto get_val = [] () { return 42; };

    // switch condition initialized inline cpp17
    switch (int x = get_val(); x) { 
        case 0:
            println("-- 0");
            { int xx = 42; }
            break;
        case 42: {
            println("-- 42");
            [[maybe_unused]]
            int z = 3;
            break;
        }
        default:
            println("-- Unknown");
            break;
    };
}

// x. return/assign switch into var:
// aka IIFE (Immediately Invoked Function Expression).
TEST_CASE("sw-3") {
    auto xx = 42;
    auto res = [xx]() {
        switch (xx) {
            case 0:  return "a";
            case 42: return "42"; 
            default: return "99";
        }
    }();

    REQUIRE(std::string_view(res) == "42");
}
