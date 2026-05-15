// #pragma once
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
// - *opt is UB if empty — always check first
// - C++23 adds monadic ops: transform, and_then, or_else
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
    if (result)                     // or result.has_value()
        std::cout << *result;       // or result.value()

    // value_or — default if empty
    int id = findUser(99).value_or(-1);

    // emplace — construct in-place
    optional<std::string> opt;  // default empty
    opt.emplace("ab"); // constructs inside optional - better, one less move
    opt = "cd";        // constructs and moves inside optional
}