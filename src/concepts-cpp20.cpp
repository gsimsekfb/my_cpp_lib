#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// Concepts
// - Named, reusable constraints on template parameters
// - concept = "compile-time" predicate that evaluates to true/false
//
// Key notes:
// - Rust Traits do everything concepts do plus runtime dispatch (dyn Trait), 
//   default implementations, and associated types.
// - Replaces SFINAE / enable_if — far more readable errors
// - requires expression: check syntax validity, return types, nested types
//   constrained auto (examples below)
// - Standard library provides ~30 built-in concepts in <concepts> and <ranges>
// - Concepts enable overload resolution — most constrained overload wins


//// A.
//// before C++20 — SFINAE, unreadable errors
template<typename T, std::enable_if_t<std::is_integral_v<T>,int> = 0>
T double_it_(T x) { return x * 2; }
    // error messages are pages long and unreadable

//// now
// define concept
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

// use
template<Numeric T>
T double_it(T x) { return x * 2; }

TEST_CASE("concep-1") {
    double_it(5);      // ✓ int
    double_it(3.14);   // ✓ double
    // double_it("hi");  // ❌ clear error: "hi" doesn't satisfy Numeric
}


//// B. 2 ways to define concept

namespace {

// 1. type trait / boolean expression
template<typename T>
concept Integral = std::is_integral_v<T>;

template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template<typename T>
concept SafeInt = std::integral<T> && sizeof(T) >= 4;

// 2. requires expression 
// check valid syntax
template<typename T>
concept Addable = requires(T a, T b) { a + b; };

template<typename T>
concept Printable = requires(T x) {
    { std::cout << x } -> std::same_as<std::ostream&>;
};

// check nested types
template<typename T>
concept Container = requires {
    typename T::value_type;
    typename T::iterator;
};

template<typename T>
concept Iterable = requires(T x) { x.begin(); x.end(); };

}


//// C. Four ways to apply a concept
// 1 — template parameter
template<std::integral T> T add(T a, T b) { return a+b; }

// 2 — requires clause
template<typename T> requires std::integral<T>
T add_(T a, T b) { return a+b; }

// 3 — abbreviated function template (cleanest)
auto add__(std::integral auto a, std::integral auto b) { return a+b; }

// // 4 — constrained auto
TEST_CASE("concep-2") {
    std::integral auto x = 42;  // x: int
    REQUIRE(x == 42);
    // std::integral auto y = "hi";  // compile error, not integral
}


