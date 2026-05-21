#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// const method and mutable
// - 
//
// Key notes:
// - const method: cannot modify member variables (except mutable)
// - const method: can only call other const methods
// - always mark methods const if they don't modify state

TEST_CASE("con-met-1") {

    //// 1. basic
    struct Circle {
        double radius;

        double area() const {           // ✓ does not modify object
            return 3.14 * radius * radius;
        }

        void setRadius(double r) {      // non-const — modifies object
            radius = r;
        }
    };

    const Circle c{5.0};
    c.area();       // ✓ const method on const object
    // c.setRadius(3); // ❌ non-const method on const object


    //// 2. mutable — allow mutation inside const method
    struct Cache {
        mutable int  hitCount = 0;    // mutable = exempt from const
        mutable bool cached   = false;
        int value;

        int get() const {
            hitCount++;               // ✓ mutable — allowed in const method
            return value;
        }
    };


    //// 3. const method with pointer member
    struct Foo {
        int* ptr;

        void fn() const {
            *ptr = 42;   // ✓ modifying pointed-to value — allowed
            // ptr  = nullptr; // ❌ modifying the pointer itself — not allowed
        }
    };

}

}