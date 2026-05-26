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


TEST_CASE("lam-1") {

    int c = 42;

    auto capture_all_val  = [=]() {};         // all by value — const inside
    auto capture_all_val_ = [=]() mutable {}; // all by value — mutable inside
    auto capture_all_ref = [&]() {};  // all by ref — mutable (ref to original)
    struct Foo { void foo() {
    auto capture_this = [this]() {};      // this ptr — access members mutably
    auto capture_this_val = [*this]() {}; // this by value — const copy (C++17)
    }};
    auto init_capture = [y = c+1]() {}; // by value — const inside (C++14)
    auto init_capture_ = [y = c+1]() mutable {}; // by value — mutable (C++14)
    string str = "abc";
    auto move_capture = [y = std::move(str)]() {}; 
        // moved-in — const inside (C++14)

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