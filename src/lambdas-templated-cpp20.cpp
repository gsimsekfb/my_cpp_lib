#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// templated lambdas
// - Templated lambdas let you write generic lambdas with "explicit template 
//   parameters" instead of relying on auto, giving you access to the actual 
//   type.
// - Syntax: []<typename T>(T x) { } — T is explicit, not deduced via auto
//   like generic lambdas: auto twice = [](auto x) { return x * 2; };
//
// Key notes:
// - Can take variadic template params: []<typename... Ts>
// - Prefer over auto params when you need the type name inside the body


TEST_CASE("tem-lam-1") {

    //// 1. main usage

    // before
    // C++14 generic lambda — auto hides the type
    auto print_ = [](auto x) {
        // what IS x? can't use sizeof(x), can't get value_type
        std::cout << x << "\n";
    };

    // now
    // C++20 — explicit template parameter
    auto print = []<typename T>(T x) {
        cout << x << ": " << sizeof(T) << "\n";
    };
    print(42);       // T = int,    sizeof = 4
    print(3.14);     // T = double, sizeof = 8
    print("hi");     // T = char*,  sizeof = 8


    //// 2. enforce constraints with concepts
    auto multiply = []<std::integral T>(T a, T b) {
        return a * b;
    };

    multiply(3, 4);      // ✓ int
    // multiply(3.0, 4.0);  // ❌ compile error — not integral


    //// 3. enforce same type for multiple params — auto can't do this

    // C++14 — auto allows different types silently
    auto add14 = [](auto a, auto b) { return a + b; };
    add14(1, 2.5);   // !! BAD, silently mixes int + double

    // C++20 — T enforces both are same type
    auto add20 = []<typename T>(T a, T b) { return a + b; };
    add20(1, 2);     // ✓ both int
    // add20(1, 2.5);   // ❌ compile error — type mismatch

    // REQUIRE(maxConnections == 128);
}
