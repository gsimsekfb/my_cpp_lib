#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// std::move()
// - std::move does NOT move — it just casts to rvalue reference
// - Actual move happens in the move constructor / move assignment operator
//
// Key notes:
// - After move: object is valid but in unspecified state/value — don't use it
// - Don't move return values — NRVO is better, move prevents it
// - std::move is free — zero runtime cost, just a cast
// - Types without move semantics fall back to copy silently !!

//// move in function return — unnecessary (NRVO does this automatically)
std::vector<int> make() {
    std::vector<int> v = {1,2,3};
    // return std::move(v);   // ❌ actually prevents NRVO — don't do this
    return v;              // ✓ compiler moves automatically
}

TEST_CASE("move-1") {

    //// main use case
    // without move — expensive copy
    std::vector<int> a = {1,2,3,4,5};
    std::vector<int> b = a;            // copies all elements — a still valid

    // with move — cheap transfer
    std::vector<int> a_ = {1,2,3,4,5};
    std::vector<int> b_ = std::move(a_); // steals a's buffer — no copy
        // a is now empty — valid but unspecified state/value


    //// move into container — avoid copy
    std::vector<std::string> names;
    std::string s = "hello";
    names.push_back(s);            // copies s
    names.push_back(std::move(s)); // moves s — s now empty ✓


    //// move in class — move constructor
    struct Buffer {
        std::vector<int> data;
        Buffer(Buffer&& other) : data(std::move(other.data)) {}  // ✓
    };

    // REQUIRE(arr[0] == 42);


}

}