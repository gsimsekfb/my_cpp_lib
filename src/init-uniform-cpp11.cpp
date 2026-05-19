#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// Uniform initialization {}
// - provides one consistent syntax to initialize any type — variables, 
//   structs, containers, and constructors.
//
// Key notes:
// - works for any type — one syntax everywhere
// - prevents narrowing conversions — safer than () or =
// - solves most vexing parse
// - prefer {} over () for construction in modern C++
// - caveat: types with initializer_list constructors may surprise you
//   e.g. vector<int>{3} = one element (3), vector<int>(3) = three zeros

TEST_CASE("ini-uni-1") {

    //// basic types
    int a {42};
    double b {3.14};
    bool c {true};

    //// structs / aggregates
    struct Point { int x, y; };
    Point p {1, 2};

    //// heap
    auto ptr = new Point {1, 2};    delete ptr;
    auto ptr_ = std::make_unique<Point>( Point {1, 2} );

    //// containers
    std::vector<int>              vec {1, 2, 3};
    std::map<std::string, int>    map { {"a", 1}, {"b", 2} };
    std::array<int, 3>            arr {1, 2, 3};
    int arr2[] = {1,2,3};

    //// constructors
    std::string str {"hello"};
    // std::thread t2 {myFunc, arg1};

    //// return value
    // Point makePoint() { return {1, 2}; }   // ✓ no type needed

    //// narrowing — key safety benefit
    // int a_ = 3.7;    // ✓ warning: silently truncates to 3
    // int a_ {3.7};     // ❌ compile error — narrowing conversion ✓

    //// most vexing parse — solved
    // Widget w();     // ❌ parsed as function declaration — classic C++ gotcha
    // Widget w{};     // ✓ always an object ✓

}

}