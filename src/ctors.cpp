#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// ctors
// - 
//
// Key notes:

struct Foo {
    int x, y;

    Foo() : x(0), y(0) {}                // default ctor
    Foo(int x, int y) : x(x), y(y) {}    // parameterized ctor
    explicit Foo(int x) : x(x), y(0) {}  // explicit — no implicit conversion

    Foo(const Foo& o) : x(o.x), y(o.y) {}    // copy ctor
    // copy assign. operator (not ctor, the obj already exists)
    Foo& operator=(const Foo& o) { 
        x = std::move(o.x); y = std::move(o.y); return *this; 
    }
        // Note: returns Foo& to enable chaining: 
        // e.g. for `a = b = c`, `b = c` returns b&, then `a = b` uses that 
        // reference; w/o the reference return, chaining would be impossible

    Foo(Foo&& o) : x(std::move(o.x)), y(std::move(o.y)) {}  // move ctor
    Foo& operator=(Foo&& o) { x = o.x; y = o.y; return *this; } // move assign.

    ~Foo() {}                                 // destructor
};


TEST_CASE("ctor-1") {

    Foo foo1, foo2;
    Foo foo3 = foo1;   // copy ctor
    Foo foo4 { foo1 }; // copy ctor
    foo3 = foo2;       // copy assign.


}

}