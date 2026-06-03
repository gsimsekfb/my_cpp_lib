#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

//// if consteval 
// - branch based on whether currently evaluating at compile time
// - different from if constexpr — constexpr branches on value, consteval on 
//   context.

// if consteval — branch on WHETHER we are in constant evaluation context
// if constexpr — branch on type/value at compile time


//// basic
constexpr int compute(int x) {
    if consteval { // if compile time evaluatable
        return x * 2;   // compile-time path ✓
    } else {
        return x * 3;   // runtime path ✓
    }
}

TEST_CASE("if-con-1") {
    constexpr int a = compute(5);   // compile time → 10
        // constexpr fns: may evaluate at compile time - forced if used in 
        // constant expression context, such as this case
    REQUIRE(a == 10);

    int b = compute(5);             // runtime      → 15
    REQUIRE(b == 15);
}


//// main use — call consteval fn safely from constexpr fn
consteval int fastSqrt(int x) { return x * x; }  // consteval — compile only
int           slowSqrt(int x) { return x * x; }  // runtime version

constexpr int sqrt(int x) {
    if consteval {
        return fastSqrt(x);   // ✓ safe — we ARE in compile-time context
    } else {
        return slowSqrt(x);   // ✓ safe — we are NOT in compile-time context
    }
}
// without if consteval — calling consteval from constexpr = compile error
// constexpr can run at runtime → consteval fn not available ❌


//// not consteval — inverse
constexpr int fn(int x) {
    if not consteval {
        // log("runtime call");   // only at runtime ✓
    }
    return x * 2;
}


}