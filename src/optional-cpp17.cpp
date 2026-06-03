// #pragma once
#include <optional>
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// std::optional<T> 
// - represents a value that may or may not be present — replacing null 
//   pointers and sentinel values like -1 or "".
//
// Key notes:
// - Identical concept as Rust Option, with the same Some(T) / None semantics, 
//   but Rust's Option<T> forces you to handle both cases (the compiler won't 
//   let you ignore it), while C++ optional lets you call *opt on an empty one
//   and get "UB".
// - Represents "value or nothing" — no heap allocation (value stored inline)
// - value() throws std::bad_optional_access if empty — use value_or() to be 
//   safe
// - Prefer optional<T> return over T* when ownership is not intended


// return optional instead of -1 / nullptr / bool out-param
std::optional<int> findUser(int id) {
    if (id == 42) return 42;
    return std::nullopt;           // empty
}

void get_files() { }

TEST_CASE("opt-1") {

    // define
    optional<int> opt_;  // default empty
    REQUIRE(opt_.has_value() == false);
    optional<int> opt__ = 42;
    REQUIRE(*opt__ == 42);

    // check and access
    auto result = findUser(42); // result: optional<int>
    // *opt is UB if empty — always check first
    if (result)                     // or result.has_value()
        std::cout << *result;       // or result.value()

    // value_or — default if empty
    int id = findUser(99).value_or(-1);

    // emplace — construct in-place
    optional<std::string> opt;  // default empty
    opt.emplace("ab"); // constructs inside optional - better, one less move
    opt = "cd";        // constructs and moves inside optional


    //// cpp23 monadic ops: transform, and_then, or_else
    std::optional<int> opt2 = 42;

    // transform — map value, leave nullopt unchanged
    opt2.transform([](int x) { return x * 2; });  // optional<int>{84}

    // and_then — chain optionals (flatMap)
    auto opt3 = opt2.and_then([](int x) -> std::optional<int> {
        if (x > 100) return x * 2;
        return std::nullopt;
    });
    REQUIRE(opt3 == std::nullopt);

    // or_else — fallback if nullopt
    std::optional<int> empty;
    auto opt4 = empty.or_else([]() -> std::optional<int> { return 0; });  // optional<int>{0}
    REQUIRE(opt4 == std::optional {0});


    // chain
    auto res = std::optional<std::string>{"hello"}
        .transform([](const std::string& s) { return s + '-'; })
        .and_then([](const std::string& s) -> std::optional<std::string> {
            if (!s.empty()) return s + ">";
            return std::nullopt;
        })
        .value_or("default");

    REQUIRE(res == "hello->");


}