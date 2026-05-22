#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"
#pragma clang diagnostic ignored "-Wunused-parameter"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// default arguments
// - Functions, member functions, ctors, and function pointers 
// - Not lambda parameters (until C++14), 
// - Not template parameters (different feature).
//
// Key notes:
// - defaults must be rightmost — no gaps allowed
// - prefer overloads over many default args for clarity
// - default args evaluated at call site — not at function definition


//// basic — rightmost params have defaults
void connect(std::string host, int port = 8080, bool ssl = false) {}

TEST_CASE("def-arg-1") {

    connect("localhost");              // port=8080, ssl=false ✓
    connect("localhost", 443);         // ssl=false ✓
    connect("localhost", 443, true);   // all explicit ✓
    // connect("localhost", , true);      // ❌ cannot skip middle arg 
}


//// declaration vs definition — default in declaration only
// header.h
void fn(int x, int y = 10);       // default here ✓

// file.cpp
void fn(int x, int y) {}          // no default here — already declared ✓
// void fn(int x, int y = 10) {}     // ❌ redefinition of default


//// can use expressions / functions as defaults
int defaultPort() { return 8080; }

// void connect(std::string host,
//             int port    = defaultPort(),     // function call ✓
//             int timeout = port * 2) {}       // ❌ cannot use other param


//// virtual functions — defaults not inherited

struct Base {
    virtual int fn(int x = 3) { return 10 * x; }
};

struct Derived : Base {
    int fn(int x = 5) override { return 20 * x; }
};

TEST_CASE("def-arg-2") {

    Base* b = new Derived();
    // !!!! uses Base default param. value, calls Derived::fn ❌ surprising
    REQUIRE(b->fn() == 60); 

}


//// default vs overload
void foo(int x, int y = 0) {}     // one function, optional y
void foo(int x)             {}     // ❌ ambiguous when called with one arg


}