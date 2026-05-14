#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wdeprecated-this-capture"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

// lambda capture this
// - In C++20, [=] no longer implicitly captures this — you must write 
// [=, this] explicitly to capture both by value and the current object.
//
// Key notes:

namespace {

//// before
//  C++17 and earlier — [=] silently captured this
struct Foo {
    int x = 10;
    void run() {
        auto fn = [=]() { return x; };  // implicitly captured this
            // warning: implicit capture of 'this' with a capture default of
            // '=' is deprecated
        fn();                           // worked but was unclear
    }
};

//// now 
// C++20 — explicit, choose your intent
struct Foo_ {
    int x = 10;
    void run() {
        auto fn1 = [=, this]() { return x; }; // capture this + locals by value
        auto fn2 = [&, this]() { x = 20; };   // capture this + locals by ref
        auto fn3 = [*this]()   { return x; }; // copy the whole object 
    }
};

//// [*this] — safest for async/deferred calls
struct Worker {
    int value = 42;
    void schedule() {
        // object may be destroyed before lambda runs!
        auto bad  = [this]() { return value; };  // ❌ dangling ptr 
        auto safe = [*this]() { return value; };  // ✓ owns its own copy
        // threadPool.post(safe);
    }
};

}
