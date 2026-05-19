#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"
#pragma clang diagnostic ignored "-Wunused-function"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

//// unique_ptr — sole ownership  |  Rust: Box<T>
// - single owner, freed automatically when out of scope
// - zero overhead over raw pointer
//
// Key notes:

class MyClass {
    int x;
    public: MyClass(int x) : x(x) {  }
    int getX() { return this->x; };
};


//// factory pattern
class Base {};
class Derived : public Base {};
std::unique_ptr<Base> create() {
    return std::make_unique<Derived>();  // ✓ polymorphism
}

TEST_CASE("uniq-1") {

    //// create
    auto up_int = std::make_unique<int>(42);
    auto up = std::make_unique<MyClass>(42);  // forwards to constructor

    //// access
    *up;          // dereference
    up.get();     // raw pointer — don't store, don't delete
    up->getX();   // arrow access
    REQUIRE(up->getX() == 42);

    //// transfer ownership
    auto p2 = std::move(up);   // ✓ move: p now null
    // auto p3 = up;           // ❌ copy: copy ctor deleted — won't compile

    //// release / reset
    up_int.reset();           // destroy object, p = null
    up_int.reset(new int(5)); // destroy old, own new
    int* raw_ptr = up_int.release(); // give up ownership — YOU must delete raw
    delete raw_ptr;

}

}