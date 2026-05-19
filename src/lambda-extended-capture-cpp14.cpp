#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// lambda extended capture
// - Extended captures let you initialize new variables directly in the capture
//   list — not just capture existing ones.
//
// Key notes:

int foo() { return 42; }

TEST_CASE("lam-ext-1") {

    // basics (C++14) — create new var in capture
    auto fn = [x = 42]() { return x; };  // x is new, not from outer scope
    auto fn_ = [x = foo()]() {};         // capture result of expression

    // move capture — move-only types (unique_ptr can't be copied)
    auto ptr = std::make_unique<int>(42);
    auto fn__ = [p = std::move(ptr)]() {        // ✓ move into lambda
        return *p;
    };
        // ptr is now empty — ownership transferred to lambda

    // rename on capture
    int longVariableName = 10;
    auto fn2 = [x = longVariableName]() { return x; };  // captured as x ✓

    // compute on capture — evaluated once at capture time
    std::vector<int> v = {1,2,3,4,5};
    auto fn3 = [size = v.size()]() { return size; };  // size fixed at capture ✓
        // even if v changes later, size stays the same

}

}