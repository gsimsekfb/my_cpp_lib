#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// constexpr
// - 1. for fns: may evaluate at compile time (forced if used in constant 
//   expression context, see item below)
// - 2. for vars: forces compile-time evaluation.
//
// constexpr int square(int n) { return n * n; }    // 1
// constexpr int val = square(5);                   // 2
//      // square(5) is guaranteed to run at compile time, val is immutable
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


//// 1. C++11 — introduced
// single return statement only, no loops/locals
constexpr int square(int n) { return n * n; }
    // for fns: may evaluate at compile time

constexpr int val = square(5);  // 25 — compile time
    // for vars: forces compile-time evaluation.
int arr[square(4)];             // ✓ array size must be compile-time constant


//// 2. C++14 — rules relaxed
// loops, locals, multiple statements now allowed
constexpr int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}
constexpr int f5 = factorial(5);  // 120


//// 3. C++17 — "if constexpr" and "constexpr lambdas"

// 3.a. if constexpr 
// - Only valid inside a template — condition must depend on template param
// - works outside of template but it is pointless to use, outside of template
//   compiler already knows all types.
// - valuates the branch at compile time — the discarded branch is
//   "never" compiled, enabling template specialization without overloads.
// - if cond. forced at compile time unlike regular constexpr w/o if

template<typename T>
auto process(T val) {
    if constexpr (std::is_integral_v<T>)
        return val * 2;      // only compiled for ints
    else
        return val + 0.5;    // only compiled for floats
}

// 3.b. constexpr lambdas also allowed in C++17
// - lambdas implicitly constexpr if body is a constant expression
// - explicit constexpr forces and a compile error if not possible
// - captures are allowed in constexpr lambdas if captured values are constexpr

// implicit constexpr if body qualifies
auto sq = [](int x) { return x * x; };
constexpr int v = sq(5);   // ✓ 25 — compiled as constexpr automatically

// explicit constexpr
auto sq_ = [](int x) constexpr { return x * x; };
constexpr int v_ = sq_(5);   // ✓


//// 4. C++20 — constexpr everywhere

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
constexpr auto isEven = [](int x) constexpr { return x % 2 == 0; };
static_assert(isEven(4));   // ✓ compile time check