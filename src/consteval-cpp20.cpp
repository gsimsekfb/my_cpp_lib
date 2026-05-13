#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// consteval 
// - declares a function that "must" execute at compile time — unlike constexpr
//   which "can" run at runtime if needed.
//
// Key notes:
// - The killer feature: consteval turns invalid inputs into compile errors 
//   rather than runtime crashes.
// - for fns and ctors only (no variables — use constexpr/constinit for those)
// - Every call MUST be a compile-time const — no runtime fallback ever
// - No binary emission — the function ceases to exist after compilation
// - Cannot take its address — no runtime existence means no pointer
// - Cannot accept runtime variables — compile error if argument isn't constant
// - throw inside = compile error, making it ideal for validated constants
// - Can call constexpr functions and forces the call to be evaluated at 
//   compile time, but constexpr cannot call consteval at runtime
// - Pair with constinit for globals: consteval computes, constinit stores


//// 1. Simple case
constexpr int sq_expr(int n) { return n*n; }  // compile OR runtime
consteval int sq_eval(int n) { return n*n; }  // compile time ONLY

TEST_CASE("con-eva-1") {

    // 1. consteval
    sq_eval(5);     // ✓ ok — 5 is a constant
    int x = 5;
    // sq_eval(x);  // ❌ compile error — x not a constant

    // 2. constexpr
    sq_expr(5);          // ✓ ok at runtime
    int y = 5;
    sq_expr(y);          // ✓ ok at runtime

    // REQUIRE(maxConnections == 128);
}


//// 2. compile-time lookup table
consteval int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

// computed at compile time — zero runtime cost
constexpr int fib10 = fibonacci(10);  // 55 

TEST_CASE("con-eva-2") {
    constexpr int fib20 = fibonacci(20);  // 6765
    static_assert(fib20 == 6765); // OK
    static_assert(fib10 == 55);   // OK

    // static_assert(fib10 == 355); // this errors w/o running the program
        // error: static assertion failed due to requirement 'fib10 == 155'
}
