#include <print>
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-parameter"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"


#include <expected>

#include "utils.h"

using namespace std;

namespace {

// 
// - std::expected<T, E> represents either a value or an error — a type-safe 
//   alternative to exceptions and error codes. == Rust Result.

//// Rust equivalent — Result<T, E>
// std::expected<T, E>      ≈  Result<T, E>
// std::unexpected(e)       ≈  Err(e)
// value()                  ≈  unwrap()
// value_or()               ≈  unwrap_or()
// and_then()               ≈  and_then()
// transform()              ≈  map()
// or_else()                ≈  or_else()
// key diff: Rust forces handling — C++ lets you ignore error (like optional)

//// key notes
// - T and E stored in obj. — no heap allocation
// - prefer over exceptions for expected/recoverable errors
// - prefer over error codes — type-safe, composable, self-documenting
// - Rust `panic!` for unrecoverable bugs, `Result` for recoverable errors; 
//   C++ `throw` for unrecoverable errors, `std::expected` (and 
//   std::variant<T, Err> before cpp23) for recoverable ones.


//// simplified illustration to show the concept — not the actual std impl.
//// Both GCC libstdc++ and LLVM libc++ use union under the hood
template<typename T, typename E>
class expected_ {
    bool has_val;
    union {
        T val;
        E err;
    };
public:
    expected_(T v) : has_val(true), val(std::move(v)) {}
    expected_(std::unexpected<E> e) 
        : has_val(false), err(std::move(e.value())) {}

    bool has_value() const { return has_val; }
    T& value() { 
        if (!has_val) throw std::bad_expected_access(err); return val;
    }
    E& error() { return err; }
    T* operator->() { return &val; }
    explicit operator bool() const { return has_val; }

    template<typename F>
    auto and_then(F&& f) { 
        if (has_val) return f(val); 
        return expected_(std::unexpected(err)); 
    }
    ~expected_() { if (has_val) val.~T(); else err.~E(); }
};


//// basic — return value or error

std::expected<int, string> divide(int a, int b) {
    if (b == 0)
        return std::unexpected("div by zero");  // error ✓
    return a / b;                                    // value ✓
}

TEST_CASE("exp-1") {
    //// check and access
    auto result = divide(10, 2);
    REQUIRE(result == 5);

    if (result)                         // or result.has_value()
        std::cout << result.value();    // 5 ✓
    else
        std::cout << result.error();    // error string

    auto res = divide(5, 0);
    REQUIRE(res == std::unexpected("div by zero"));

    try {
        auto res_ = res.value();  // throws
    } catch(const std::exception& ex) {
        println(ex.what()); // Bad expected access
    }


    //// chain — and_then / transform / or_else
    auto res_ = divide(10, 2)
        .and_then([](int x) -> std::expected<int, std::string> {
            return x * 2;              // chain another expected ✓
        })
        // transform: map over value, leave error unchanged
        .transform([](int x) -> string {
            return std::to_string(x);  // transform value ✓
        })
        // transform error (note: meaningless in this example since or_else
        // is providing default error)
        .transform_error([](const std::string& e) -> std::string {
            return "wrapped: " + e;
        })
        .or_else([](const std::string& e) -> std::expected<string, string> {
            return "default";  // recover with default value on error
        });

}

//// custom error type
enum class MathErr { DivByZero, Overflow, NaN };

std::expected<double, MathErr> safeSqrt(double x) {
    if (x < 0) return std::unexpected(MathErr::NaN);
    return std::sqrt(x);
}


//// vs exceptions
int divide_ex(int a, int b) {
    if (b == 0) 
        throw std::runtime_error("div by zero");  // hidden control flow
    return a / b;
}

std::expected<int, std::string> divide_ex2(int a, int b) {
    if (b == 0) 
        return std::unexpected("div by zero");    // explicit ✓
    return a / b;
}


//// vs error code
std::pair<int, int> divide_ec(int a, int b) {  // value + error code — clunky
    if (b == 0) return {0, -1};
    return {a / b, 0};
}



}