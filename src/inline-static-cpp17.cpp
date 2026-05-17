// #pragma once
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// inline static
// - C++17 feature — define static members inside the class body
// - Eliminates the separate .cpp definition requirement
//
// Key notes:
// - Safe in headers — inline guarantees one definition across all translation 
//   units
// - constexpr static is implicitly inline in C++17 — no need to write both
// - Non-const static members still need inline explicitly
// - Prefer static constexpr for compile-time constants, inline static for
//   mutable globals
//


//// 1. before/now

// before C++17 — must define outside class in .cpp
struct Config {
    static int maxUsers;      // declaration only
};
// int Config::maxUsers = 100;   // definition in .cpp — required

// now, C++17 inline static — define in header, one definition across all TUs
struct Config_ {
    inline static int maxUsers = 100;    // definition here ✓
    inline static std::string host = "localhost";
};


//// 2. combine with constexpr — most common use
struct Limits {
    inline static std::string name = "app"; 
        // non-const needs inline explicitly

    static constexpr int maxUsers  = 100;   
    static constexpr double pi     = 3.14159;
        // constexpr implies inline in C++17
};
// key diffs:
// 1. mutability   — constexpr: immutable;  inline static: mutable
// 2. timing       — constexpr: compile time; inline static: runtime init
// 3. types        — constexpr: literal types only (int, double, etc.)
//                   inline static: any type (string, vector, custom class)


TEST_CASE("inline-stat-1") {
    auto limits = Limits {};
    REQUIRE(limits.maxUsers == 100);
    REQUIRE(Limits::maxUsers == 100);

    REQUIRE(limits.name == "app");
    limits.name = "qqq";
    REQUIRE(limits.name == "qqq");
}
