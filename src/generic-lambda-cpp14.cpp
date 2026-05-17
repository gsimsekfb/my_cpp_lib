#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {


// generic lambdas
// - auto in a lambda parameter is syntactic sugar for a template — 
// - the compiler generates a templated operator() equivalent to
// template<typename T> auto operator()(T x).
//
// auto f = [](auto x) { return x * 2; };
//
// Key notes:
// - auto a, auto b — two "independent" types; 
//   (use <typename T>(T a, T b) to enforce same types)


//// 1. A generic lambda
auto twice = [](auto x) { return x * 2; };
    // De-sugared equivalent
    struct __lambda {
        template<typename T>
        auto operator()(T x) const { return x * 2; }
    };

auto print = [](auto x) { std::cout << x << "\n"; };
// print(42);       // operator()(int)
// print(3.14);     // operator()(double)
// print("hello");  // operator()(const char*)


//// 2. C++20 — same type enforced
auto add20 = []<typename T>(T a, T b) { return a + b; };
// add20(1, 2);     // ✓
// add20(1, 2.5);   // ❌ — both must be same type T



}