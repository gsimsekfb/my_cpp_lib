#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// Concepts
// - 
//
// Key notes:


TEST_CASE("multi-d-1") {

    //// cpp23
    struct Matrix {
        int data[3][3] = {};
        
        // cpp23
        int& operator[](size_t i, size_t j) { return data[i][j]; }
        const int& operator[](size_t i, size_t j) const { return data[i][j]; }
            // pre-cpp23
            // error: overloaded 'operator[]' cannot have more than one 
            // parameter before C++2b

    };

    Matrix m;
    m[0, 1] = 42;   // ✓ C++23
    m[1, 2];        // ✓
    REQUIRE(m[0,0] == 0);
    REQUIRE(m[2,2] == 0);

    // before cpp23 workaround: operator() (function call)
    struct Matrix_ {
        int data[3][3] = {};
        int& operator()(size_t i, size_t j) { return data[i][j]; }
    };
    Matrix_ m_;
    m_(0, 1) = 42;   // ❌ looks like a function call, not indexing


}

}