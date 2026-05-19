#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// decltype auto
//
// key notes:
// - problem: auto: always deduces value type — strips &, const, volatile
// - fix: decltype(auto): preserves exact type including &, const, volatile
// - Main use: forwarding functions that must preserve return type exactly
// - (x) vs x matters — (x) is lvalue expression → deduced as int&


//// 1. main use case

// return type deduction
int& getRef(int& x) { return x; }

// auto         fn1() { return getRef(4); } // returns int  — copy, ref stripped
// decltype(auto) fn2() { return getRef(4); }  // returns int& — ref preserved 

TEST_CASE("dec-aut-1") {

    // auto strips references — decltype(auto) preserves them
    int x = 42;
    int& ref = x;

    auto           a = ref; // int  — reference stripped
    decltype(auto) b = ref; // int& — reference preserved ✓

    // REQUIRE(arr[0] == 42);
}


// danger — returning ref to local
/* 
decltype(auto) bad() {
    int x = 42;
    return (x);    // ❌ returns int& to local — dangling!
    // (x) is an lvalue expression — decltype(auto) sees int&
}
*/

decltype(auto) good() {
    int x = 42;
    return x;      // ✓ returns int — copy, safe
    // x is just a name — decltype(auto) sees int
}

// perfect forwarding return
template<typename F, typename... Args>
decltype(auto) call(F&& fn, Args&&... args) {
    return std::forward<F>(fn)(std::forward<Args>(args)...);
        // preserves whatever the function actually returns ✓
}

}