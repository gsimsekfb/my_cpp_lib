#include <cstddef>
#pragma clang diagnostic ignored "-Wunused-variable"
#pragma clang diagnostic ignored "-Wunused-value"

#define CATCH_CONFIG_MAIN  // Tells Catch2 to provide a main()
#include "../catch/catch_amalgamated.hpp"

#include "utils.h"

using namespace std;

namespace {

// dynamic_cast
// - dynamic_cast safely downcasts a pointer/reference to a derived type at 
//   runtime — returns nullptr if the cast is invalid.
//
// Key notes:
// - requires at least one virtual function in base (usually virtual dtor)
// - pointer cast: returns nullptr on failure — always check result
// - reference cast: throws std::bad_cast on failure — use try/catch
// - has runtime cost — RTTI lookup (avoid in hot paths)
// - sidecast: unique to dynamic_cast — static_cast can't do this
// - if you need dynamic_cast a lot — consider redesigning with virtual 
//   functions


TEST_CASE("dynamic-cast-1") {

    //// basic downcast — base to derived
    struct Animal { virtual ~Animal() {} };  // must have virtual function
    struct Dog : Animal { void bark() {} };
    struct Cat : Animal { void meow() {} };

    Animal* anim = new Dog();

    // pointer cast — returns nullptr if wrong type
    Dog* dog = dynamic_cast<Dog*>(anim);   // ✓ a is actually Dog
    Cat* cat = dynamic_cast<Cat*>(anim);   // nullptr — a is not Cat
    REQUIRE(cat == nullptr);

    if (Dog* dog = dynamic_cast<Dog*>(anim))
        dog->bark();                     // ✓ safe ✓

    // reference cast — throws std::bad_cast if wrong type
    try {
        Dog& dog = dynamic_cast<Dog&>(*anim);   // ✓
        Cat& cat = dynamic_cast<Cat&>(*anim);   // ❌ throws std::bad_cast
    } catch (std::bad_cast& e) {
        // ...
    }


    //// sidecast — across inheritance hierarchy
    struct Base_1 { virtual ~Base_1(){} };
    struct Base_2 { virtual ~Base_2(){} };
    struct Derived : Base_1, Base_2 {};

    Base_1* base_1 = new Derived();
    // ✓ sidecast — Base_1* to Base_2* via Derived ✓
    Base_2* base_2 = dynamic_cast<Base_2*>(base_1);   


    //// dynamic_cast vs static_cast
    Animal* anim_ = new Dog();
    Dog* d_ = static_cast<Dog*>(anim_);  // no runtime check — UB if wrong type
        // !! use only when you're 100% certain of the type
    Dog* dd = dynamic_cast<Dog*>(anim_); // runtime check — nullptr if wrong


    //// requires polymorphic type
    struct Foo {};                    // no virtual functions
    struct Bar : Foo {};

    Foo* f = new Bar();
    // Bar* b = dynamic_cast<Bar*>(f);  // compile error — Foo not polymorphic


}

}