#include <array>
#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;


// constinit ("const" is confusing; "const" is "compile time" in this context)
// guarantees a variable is initialized at compile time (preventing the static
// initialization order fiasco), while still allowing it to be "mutated" at 
// runtime — unlike `constexpr`, which locks the value permanently.
//
// constinit = compile-time init only 
//                      (still mutable, not usable in constant expressions)
// constexpr = const + compile-time init 
//                      (immutable, usable in const expressions)
//
// Key notes:
// - Main use case: preventing static initialization order fiasco while keeping 
//   mutability
// - only for variables
// - Only for static/thread-local storage duration (globals, static locals, 
//   thread_local)
// - Guarantees initialization happens at compile time 
//   (prevents silent runtime init)
// - Does not imply const — variable remains mutable
// - Does not make it usable in constant expressions



//// 1. now, fixed init-order fiasco w/ constinit
/* 
a.cpp
    constinit int base = 10; // guaranteed at compile time

b.cpp
    constexpr int derived = 10 * 2; // OK: no runtime dep on base
*/

// before
// what is init-order fiasco ?
/* 
a.cpp
    int base = 10; // runtime-initialized

b.cpp
    extern int base;
    int derived = base * 2; // 😱 base may be 0 or 10 or garbage here!
        // C++ does NOT guarantee a.cpp runs first
        // derived could be 0, 20, or garbage
*/

constinit int maxConnections = 128;
constinit double timeoutSeconds = 30.0;
    // - Constant-initialized at compile time (guaranteed no static-init order
    //   fiasco)
    // - Still mutable at runtime

TEST_CASE("con-ini-1") {
    REQUIRE(maxConnections == 128);
}


//// 2. Mut/Immut large table initialized once at compile time

// Note: 
// Use `constexpr` if immutable, `constinit` if you need to mutate it later 
constinit std::array<int, 5> arr = []() {
    std::array<int, 5> a; a.fill(0); return a;
}();

TEST_CASE("con-ini-2") {
    REQUIRE(arr == std::array<int, 5> {0,0,0,0,0});
}