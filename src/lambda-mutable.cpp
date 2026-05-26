#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-lambda-capture"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// 
// - By default lambdas capture by value and treat captured copies as const —
//   mutable removes that restriction.
//
// Key notes:
// - by default: value captures are const inside lambda body
// - mutable: removes const from ALL value captures — not selectable per capture
// - mutable does not affect reference captures — refs always modifiable
// - state persists between calls — lambda owns its captured copies
// - common use: counters, generators, accumulators stored as lambdas


TEST_CASE("lam-mut-1") {

    //// without mutable — captured copies are const
    int x = 10;
    auto lam = [x]() {
        // x++;        // ❌ compile error — x is const copy
    };

    //// with mutable — captured copies are modifiable
    auto lam_ = [x]() mutable {
        x++;        // ✓ modifies the lambda's own copy
        return x;
    };

    REQUIRE(lam_() == 11); 
    REQUIRE(lam_() == 12); // lambda owns its copy, persists between calls


    //// stateful lambda — counter
    auto counter = [count = 0]() mutable {
        return ++count;
    };

    counter();   // 1
    counter();   // 2
    counter();   // 3 ✓ — state persists in lambda


    {

    //// mutable vs ref capture
    int x = 10;
    auto byVal = [x]() mutable { ++x; };  // modifies copy — original unchanged
    auto byRef = [&x]() { ++x; };  // modifies original — no mutable needed
    const int& ref = x;
    // auto byConsRef = [ref]() { ++ref; };
        //  error: cannot assign to a variable captured by copy in a 
        //         non-mutable lambda

    byVal(); std::cout << x;  // 10 — original unchanged ✓
    REQUIRE(x == 10);
    
    byRef(); std::cout << x;  // 11 — original modified ✓
    REQUIRE(x == 11);

    }

}

}