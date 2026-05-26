#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// - An aggregate is a class/struct with no user-declared constructors, 
//   no private/protected members, no virtual functions — enabling aggregate 
//   initialization with {}.

//
// Key notes:
// - use std::is_aggregate_v<T> to check at compile time
// - designated initializers (.member = val) only work on aggregates
// - adding any constructor breaks aggregate


//// aggregate — simple struct, no constructor needed
struct Point {
    int x, y, z;
};


TEST_CASE("agg-cla-1") {

    Point p {1, 2, 3};       // aggregate init ✓

}

}