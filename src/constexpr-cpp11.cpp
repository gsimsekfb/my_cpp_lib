#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// constexpr
// - marks a function or variable as potentially evaluable at compile time — 
//   the compiler decides based on context, unlike consteval which forces it.
//
// Key notes:
// - constexpr: functions, constructors, variables, if constexpr
// - constexpr variables are implicitly const
// - Compile time if possible, runtime if needed — compiler decides
// - C++11: single return only; C++14: loops/locals allowed
// - C++17: if constexpr for compile-time branching; lambdas allowed
// - C++20: std::vector, std::string, virtual functions all supported
// - Does NOT guarantee compile-time — use consteval if that guarantee matters
// - Functions must be defined in headers (like templates) — not .cpp files
// - Preferred over macros and magic numbers for compile-time constants


//// C++11 — introduced
// single return statement only, no loops/locals
constexpr int square(int n) { return n * n; }

constexpr int val = square(5);  // 25 — compile time
int arr[square(4)];             // ✓ array size must be compile-time constant


//// C++14 — rules relaxed
// loops, locals, multiple statements now allowed
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}
constexpr int f5 = factorial(5);  // 120


//// C++17 — if constexpr, constexpr lambdas
// e.g. branch at compile time based on type
template<typename T>
auto process(T val) {
    if constexpr (std::is_integral_v<T>)
        return val * 2;       // only compiled for ints
    else
        return val + 0.5;    // only compiled for floats
}

// constexpr lambdas also allowed in C++17
constexpr auto sq = [](int x) { return x * x; };
constexpr int v = sq(9);  // 81


//// C++20 — constexpr everywhere
// std::vector, std::string now constexpr
constexpr int sumVec() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    int s = 0;
    for (int x : v) s += x;
    return s;
}
constexpr int total = sumVec();  // 15 — at compile time ✓

// virtual functions can now be constexpr
struct Base {
    virtual constexpr int value() { return 1; }
};


//// All versions - practical uses

// compile-time sizes
constexpr size_t BUFFER_SIZE = 1024;
constexpr size_t MAX_USERS   = 100;

// prefer over macros and magic numbers
#define MAX_USERS 100 // BAD, macro — no type, no scope, no debugger visibility
int arr_[100];        // BAD, magic number — unexplained raw value

constexpr int MAX_USERS_ = 100;  // GOOD, typed, scoped, debuggable ✓
int arr__[MAX_USERS_];           // GOOD

// math helpers
constexpr double PI = 3.14159265358979;
constexpr double toRad(double deg) { return deg * PI / 180.0; }

// type traits / template metaprogramming
template<typename T>
constexpr bool isPointer = std::is_pointer_v<T>;

// static_assert validation
static_assert(factorial(5) == 120, "math is broken");
